#include "klib/kmemory.h"

uint32_t mem_start = 0x100000;

uint32_t
ethoc (uint32_t size, int align, uint32_t *paddr)
{
  if (align == 1 && (mem_start & 0xFFFFF000))
  {
    mem_start &= 0xFFFFF000;
    mem_start += 0x100000;
  }

  if (paddr)
    *paddr = mem_start;

  uint32_t ret = mem_start;
  mem_start += size;
  return ret;
}
