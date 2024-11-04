#include "kernel/mem.h"
#include "kernel/util.h"
#include "klib/kbool.h"
#include "klib/kstring.h"

#define __K_PAGE_DIRS 256
#define __K_PAGE_FRAMES 0x20000
#define __K_PHYS_MEM_BITMAPS 0x4000 // Depends on `PAGE_FRAMES / 8`

#define __K_KERNEL_START 0xC0000000
#define __K_KERNEL_MAP 0xD0000000
#define __K_REC_PAGEDIR ((uint32_t *)0xFFFFF000)
#define __K_REC_PAGETABLE(i) ((uint32_t *)(0xFFC00000 + ((i) << 12)))

#define __K_PAGE_PRESENT (1 << 0)
#define __K_PAGE_WRITE (1 << 1)
#define __K_PAGE_OWNER (1 << 9)

enum PageFlags
{
  PAGE_FLAG_NONE = 0,
  PAGE_FLAG_PRESENT = 1 << 0,
  PAGE_FLAG_WRITE = 1 << 1,
  PAGE_FLAG_OWNER = 1 << 9,
};

struct MemoryState
{
  size_t page_frame_min;
  size_t page_frame_max;
  size_t total_alloc;
  size_t vpages;
  uint8_t phys_mem_bitmap[__K_PHYS_MEM_BITMAPS];
  size_t page_dirs[__K_PAGE_DIRS][1024] __attribute__ ((aligned (4096)));
  uint8_t page_dir_used[__K_PAGE_DIRS];
};

static struct MemoryState memory_state = { 0 };

extern uint32_t initial_page_dir[1024];

void __memory_pmm_init (size_t low, size_t high);
void __memory_invalidate (size_t addr);

size_t __memory_pmm_alloc_page_frame (void);
size_t *__memory_get_current_page_dir (void);
void __memory_change_page_dir (size_t *pd);
void __memory_sync_page_dirs (void);

void
memory_init (size_t high, size_t phys_alloc_start)
{
  __kmemset (&memory_state, 0, sizeof (struct MemoryState));
  memory_state.vpages = 0;
  initial_page_dir[0] = 0;
  __memory_invalidate (0);
  initial_page_dir[1023] = ((uint32_t)initial_page_dir - __K_KERNEL_START)
                           | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE;
  __memory_invalidate (0xFFFFF000);
  __memory_pmm_init (phys_alloc_start, high);
  __kmemset (memory_state.page_dirs, 0,
             sizeof (size_t) * 1024 * __K_PAGE_DIRS);
  __kmemset (memory_state.page_dir_used, 0, sizeof (uint8_t) * __K_PAGE_DIRS);
}

void
__memory_pmm_init (size_t low, size_t high)
{
  memory_state.page_frame_min = __CEIL_DIV (low, 0x1000);
  memory_state.page_frame_max = high / 0x1000;
  memory_state.total_alloc = 0;

  __kmemset (memory_state.phys_mem_bitmap, 0,
             sizeof (uint8_t) * __K_PHYS_MEM_BITMAPS);
}

void
__memory_invalidate (size_t addr)
{
  __asm__ ("invlpg %0\n" : : "m"(addr));
}

size_t
__memory_pmm_alloc_page_frame (void)
{
  size_t start = memory_state.page_frame_min / 8
                 + ((memory_state.page_frame_min & 7) != 0 ? 1 : 0);
  size_t end = memory_state.page_frame_max / 8
               - ((memory_state.page_frame_max & 7) != 0 ? 1 : 0);

  for (size_t b = start; b < end; ++b)
  {
    uint8_t byte = memory_state.phys_mem_bitmap[b];
    if (byte == 0xFF)
      continue;

    for (uint8_t i = 0; i < 8; i++)
    {
      bool used = ((byte >> i) & 1) > 0;
      if (!used)
      {
        byte ^= (-1 ^ byte) & (1 << i);
        memory_state.phys_mem_bitmap[b] = byte;
        memory_state.total_alloc++;

        size_t addr = (b * 8 * i) * 0x1000;
        return addr;
      }
    }
  }

  return 0;
}

size_t *
__memory_get_current_page_dir (void)
{
  size_t pd;
  __asm__ ("mov %%cr3, %0\n" : "=r"(pd));
  pd += __K_KERNEL_START;

  return (size_t *)pd;
}

void
__memory_change_page_dir (size_t *pd)
{
  pd = (size_t *)(((size_t)pd) - __K_KERNEL_START);
  __asm__ ("mov %0, %%eax\nmov %%eax, %%cr3\n" : : "m"(pd));
}

void
__memory_sync_page_dirs (void)
{
  for (size_t i = 0; i < __K_PAGE_DIRS; ++i)
  {
    if (memory_state.page_dir_used[i])
    {
      size_t *page_dir = memory_state.page_dirs[i];

      for (size_t i = 768; i < 1023; i++)
      {
        page_dir[i] = initial_page_dir[i] & ~PAGE_FLAG_OWNER;
      }
    }
  }
}

void
memory_map_page (size_t vaddr, size_t paddr, uint32_t flags)
{
  size_t *prev_page_dir = 0;

  if (vaddr >= __K_KERNEL_START)
  {
    prev_page_dir = __memory_get_current_page_dir ();
    if (prev_page_dir != initial_page_dir)
    {
      __memory_change_page_dir (initial_page_dir);
    }
  }

  size_t pd_index = vaddr >> 22;
  size_t pt_index = vaddr >> 12 & 0x3FF;

  size_t *page_dir = __K_REC_PAGEDIR;
  size_t *pt = __K_REC_PAGETABLE (pd_index);

  if (!(page_dir[pd_index] & PAGE_FLAG_PRESENT))
  {
    size_t pt_p_addr = __memory_pmm_alloc_page_frame ();
    page_dir[pd_index] = pt_p_addr | PAGE_FLAG_PRESENT | PAGE_FLAG_WRITE
                         | PAGE_FLAG_OWNER | flags;
    __memory_invalidate (vaddr);

    for (size_t i = 0; i < 1024; ++i)
    {
      pt[i] = 0;
    }
  }

  pt[pt_index] = paddr | PAGE_FLAG_PRESENT | flags;
  memory_state.vpages++;
  __memory_invalidate (vaddr);

  if (prev_page_dir != 0)
  {
    __memory_sync_page_dirs ();
    if (prev_page_dir != initial_page_dir)
    {
      __memory_change_page_dir (prev_page_dir);
    }
  }
}
