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
__kmemmove (void *dst, const void *src, size_t n)
{
  // Code provided by Supmaxred.
  uint8_t *d = (uint8_t *)dst;
  const uint8_t *s = (const uint8_t *)src;

  if (d < s)
  {
    while (n >= 4)
    {
      *(uint32_t *)d = *(const uint32_t *)s;
      d += 4;
      s += 4;
      n -= 4;
    }

    if (n >= 2)
    {
      *(uint16_t *)d = *(const uint16_t *)s;
      d += 2;
      s += 2;
      n -= 2;
    }

    if (n > 0)
    {
      *d = *s;
    }
  }
  else
  {
    d += n;
    s += n;

    while (n >= 4)
    {
      d -= 4;
      s -= 4;
      *(uint32_t *)d = *(const uint32_t *)s;
      n -= 4;
    }

    if (n >= 2)
    {
      d -= 2;
      s -= 2;
      *(uint16_t *)d = *(const uint16_t *)s;
      n -= 2;
    }

    if (n > 0)
    {
      d--;
      s--;
      *d = *s;
    }
  }

  return dst;
}

void *
__kmemset (void *blk, int c, size_t n)
{
  for (size_t i = 0; i < n; i++)
    ((uint8_t *)blk)[i] = c;
  return blk;
}

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
