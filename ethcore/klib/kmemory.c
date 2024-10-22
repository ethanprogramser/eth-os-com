#include "klib/kmemory.h"

uint32_t mem_start = 0x100000;
void *
__kmemcpy (void *dst, const void *src, size_t n)
{
  for (size_t i = 0; i < n; i++)
    ((uint8_t *)dst)[i] = ((uint8_t *)src)[i];
  return dst;
}

void *
__kmemset (void *blk, int c, size_t n)
{
  for (size_t i = 0; i < n; i++)
    ((uint8_t *)blk)[i] = c;
  return blk;
}

uint32_t ethoc(uint32_t size, int align, uint32_t *paddr) {
      if(align == 1 && (mem_start & 0xFFFFF000)) {
          mem_start &= 0xFFFFF000;
          mem_start += 0x100000;
      }

      if(paddr) *paddr = mem_start;

      uint32_t ret = mem_start;
      mem_start+=size;
      return ret;
}
