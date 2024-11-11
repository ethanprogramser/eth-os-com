#include "kernel/gdt.h"
#include "klib/kmemory.h"

extern void gdt_flush (size_t);
extern void tss_flush (void);

struct GdtEntry gdt_entries[6];
struct GdtPtr gdt_ptr;
struct TssEntry tss_entry;

static inline void __tss_write (uint32_t num, uint16_t ss0, uint32_t esp0);
static inline void __gdt_set_gate (uint32_t num, size_t base, uint32_t limit,
                                   uint8_t access, uint8_t gran);

void
gdt_init (void)
{
  gdt_ptr.limit = (sizeof (struct GdtEntry) * 6) - 1;
  gdt_ptr.base = (size_t)&gdt_entries;

  __gdt_set_gate (0, 0, 0, 0, 0);                // Null segment
  __gdt_set_gate (1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel code segment
  __gdt_set_gate (2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel data segment
  __gdt_set_gate (3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User code segment
  __gdt_set_gate (4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User data segment
  __tss_write (5, 0x10, 0x0);

  gdt_flush ((size_t)&gdt_ptr);
  tss_flush ();
}

static inline void
__tss_write (uint32_t num, uint16_t ss0, uint32_t esp0)
{
  size_t base = (size_t)&tss_entry;
  size_t limit = base + sizeof (tss_entry);

  __gdt_set_gate (num, base, limit, 0xE9, 0x00);
  __kmemset (&tss_entry, 0, sizeof (tss_entry));

  tss_entry.ss0 = ss0;
  tss_entry.esp0 = esp0;

  tss_entry.cs = 0x08 | 0x3;
  tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs
      = 0x10 | 0x3;
}

static inline void
__gdt_set_gate (uint32_t num, size_t base, uint32_t limit, uint8_t access,
                uint8_t gran)
{

  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit = (limit & 0xFFFF);
  gdt_entries[num].flags = (limit >> 16) & 0x0F;
  gdt_entries[num].flags |= (gran & 0xF0);

  gdt_entries[num].access = access;
}
