#ifndef __K_KLIB_STRINGS_H__
#define __K_KLIB_STRINGS_H__

#include "klib/kctype.h"
#include "klib/kdef.h"

void __kbzero (void *dst, size_t n);
void __kbcopy (const void *src, void *dst, size_t n);
int __kstrcasecmp (const char *str1, const char *str2);
int __kstrncasecmp (const char *str1, const char *str2, size_t n);

static inline char
__kfoldcase (char c)
{
  if (__kisalpha (c))
    return __ktolower (c);
  return c;
}

#endif // __K_KLIB_STRINGS_H__
