#include "klib/kmemory.h"

uint32_t mem_start = 0x100000;

uint32_t
ethoc (uint32_t size, int align, uint32_t *paddr)
{
  if (align > 1) {
    mem_start = (mem_start + align - 1) & ~(align - 1);
  }

  if (mem_start + size < mem_start) {
    return 0; // Error: overflow
  }

  if (paddr)
    *paddr = mem_start;

  uint32_t allocated = mem_start;
  mem_start += size;
  return allocated;
}
