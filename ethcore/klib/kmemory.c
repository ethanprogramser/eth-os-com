#include "klib/kmemory.h"

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
