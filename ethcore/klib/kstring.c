#include "klib/kstring.h"

int
__kstrlen (const char *str)
{
  int n = 0;
  for (; *str; str++, n++)
    ;
  return n;
}

void
__kstrcpy (char *dst, const char *src)
{
  for (; *src; src++, dst++)
    *dst = *src;
}

void
__kstrncpy (char *dst, const char *src, int n)
{
  for (int i = 0; i < n && src[i]; i++)
    dst[i] = src[i];
}
