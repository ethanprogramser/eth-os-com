#include "kernel/kstringutils.h"
#include "klib/kctype.h"
#include "klib/kstring.h"

char *
string_trim (char *str)
{
  for (; __kisspace (*str); str++)
    ;
  if (*str)
  {
    char *p = str;
    for (; *p; p++)
      ;
    while (__kisspace (*(--p)))
      ;
    p[1] = 0;
  }
  return str;
}

void
string_mid (char *dst, const char *src, size_t start, size_t len)
{
  if (len == 0)
    return;
  size_t src_len = __kstrlen (src);
  if (start >= src_len)
  {
    dst[0] = 0;
    return;
  }
  if (len > 0)
  {
    for (size_t i = start, j = 0; j < len && src[i]; i++, j++)
      dst[j] = src[i];
    dst[start + len] = 0;
  }
  else
  {
    size_t j = 0;
    for (size_t i = start; src[i]; i++, j++)
      dst[j] = src[i];
    dst[start + j] = 0;
  }
}

size_t
string_index (const char *str, char c)
{
  return (size_t)(__kstrchr (str, c) - str);
}

char *
string_empty (char *str)
{
  if (str != 0)
    str[0] = 0;
  return str;
}
