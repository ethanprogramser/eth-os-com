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
  for (; *src; *dst++ = *src++)
    ;
}

void
__kstrncpy (char *dst, const char *src, int n)
{
  for (; *src && n > 0; *dst++ = *src++, --n)
    ;
}

int
__kstrcmp (const char *str1, const char *str2)
{
  while (*str1 == *str2++)
    if (*str1++ == 0)
      return 0;
  return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}
