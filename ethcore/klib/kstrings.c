#include "klib/kstrings.h"
#include "klib/kstring.h"

void
__kbzero (void *dst, size_t n)
{
  __kmemset (dst, 0, n);
}

void
__kbcopy (const void *src, void *dst, size_t n)
{
  __kmemmove (dst, src, n);
}

int
__kstrcasecmp (const char *str1, const char *str2)
{
  for (; __kfoldcase (*str1) == __kfoldcase (*str2); ++str1, ++str2)
    if (*str1 == 0)
      return 0;
  return __kfoldcase (*(unsigned const char *)str1)
                 < __kfoldcase (*(unsigned const char *)str2)
             ? -1
             : 1;
}

int
__kstrncasecmp (const char *str1, const char *str2, size_t n)
{
  if (!n)
    return 0;
  do
  {
    if (__kfoldcase (*str1) != __kfoldcase (*str2++))
      return __kfoldcase (*(unsigned const char *)str1)
             - __kfoldcase (*(unsigned const char *)--str2);
    if (*str1++ == 0)
      break;
  } while (--n);
  return 0;
}
