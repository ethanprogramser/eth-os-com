#include "klib/kstring.h"
#include "klib/kbool.h"
#include "klib/kctype.h"
#include "klib/kstrings.h"

size_t
__kstrspn (const char *str, const char *accept)
{
  const char *p = str;
cont:
  char c = *p++;
  char ac;
  for (const char *ap = accept; (ac = *ap++) != '\0';)
  {
    if (ac == c)
      goto cont;
  }
  return p - 1 - str;
}

size_t
__kstrcspn (const char *str, const char *reject)
{
  for (const char *p = str;;)
  {
    char c = *p++;
    const char *rp = reject;
    char rc;
    do
    {
      if ((rc = *rp++) == c)
        return p - 1 - str;
    } while (rc);
  }
}

size_t
__kstrlen (const char *str)
{
  size_t len = 0;
  while (*(str++))
    ++len;
  return len;
}

size_t
__kstrnlen (const char *str, size_t max_len)
{
  size_t len = 0;
  for (; len < max_len && *str; str++)
    len++;
  return len;
}

char *
__kstrcpy (char *dst, const char *src)
{
  char *o_dst = dst;
  while ((*dst = *src) != 0)
  {
    dst++;
    src++;
  }
  return o_dst;
}

char *
__kstpcpy (char *dst, const char *src)
{
  while ((*dst = *src) != 0)
  {
    dst++;
    src++;
  }
  return dst;
}

char *
__kstrncpy (char *dst, const char *src, size_t n)
{
  size_t i;
  for (i = 0; i < n && src[i] != 0; ++i)
    dst[i] = src[i];
  for (; i < n; ++i)
    dst[i] = 0;
  return dst;
}

size_t
__kstrlcpy (char *dst, const char *src, size_t n)
{
  size_t i;
  for (i = 0; i + 1 < n && src[i] != 0; ++i)
    dst[i] = src[i];
  if (n)
    dst[i] = 0;
  for (; src[i] != 0; ++i)
    ;
  return i;
}

char *
__kstrchr (const char *str, int c)
{
  char ch = c;
  for (;; ++str)
  {
    if (*str == ch)
      return (char *)str;
    if (!*str)
      return (char *)0;
  }
}

char *
__kindex (const char *str, int c)
{
  return __kstrchr (str, c);
}

char *
__kstrchrnul (const char *str, int c)
{
  char ch = c;
  for (;; ++str)
    if (*str == ch || !*str)
      return (char *)str;
}

void *
__kmemchr (const void *ptr, int c, size_t sz)
{
  char ch = c;
  const char *p = (const char *)ptr;
  for (size_t i = 0; i < sz; ++i)
    if (p[i] == ch)
      return (char *)(p + i);
  return (void *)0;
}

char *
__kstrrchr (const char *str, int c)
{
  char *last = (char *)0;
  char ch;
  for (; (ch = *str); ++str)
    if (ch == c)
      last = (char *)str;
  return last;
}

char *
__krindex (const char *str, int c)
{
  return __kstrrchr (str, c);
}

char *
__kstrcat (char *dst, const char *src)
{
  size_t dst_len = __kstrlen (dst);
  size_t i;
  for (i = 0; src[i] != 0; i++)
    dst[dst_len + i] = src[i];
  dst[dst_len + i] = 0;
  return dst;
}

char *
__kstrncat (char *dst, const char *src, size_t n)
{
  size_t dst_len = __kstrlen (dst);
  size_t i;
  for (i = 0; i < n && src[i] != 0; i++)
    dst[dst_len + i] = src[i];
  dst[dst_len + i] = 0;
  return dst;
}

char *
__kstrstr (const char *hay, const char *needle)
{
  char nch, hch;
  if ((nch = *needle++) != 0)
  {
    size_t len = __kstrlen (needle);
    do
    {
      do
      {
        if ((hch = *hay++) == 0)
          return (char *)0;
      } while (hch != nch);
    } while (__kstrncmp (hay, needle, len) != 0);
    --hay;
  }
  return (char *)hay;
}

char *
__kstrcasestr (const char *hay, const char *needle)
{
  char nch, hch;
  if ((nch = *needle++) != 0)
  {
    size_t len = __kstrlen (needle);
    do
    {
      do
      {
        if ((hch = *hay++) == 0)
          return (char *)0;
      } while (__ktoupper (hch) != __ktoupper (nch));
    } while (__kstrncasecmp (hay, needle, len) != 0);
  }
  return (char *)hay;
}

char *
__kstrpbrk (const char *str, const char *accept)
{
  while (*str)
    if (__kstrchr (accept, *str++))
      return (char *)--str;
  return (char *)0;
}

char *
__kstrtok_r (char *str, const char *delim, char **saved_str)
{
  if (!str)
  {
    if (!saved_str || *saved_str == (char *)0)
      return (char *)0;
    str = *saved_str;
  }

  size_t token_start = 0;
  size_t token_end = 0;
  size_t str_len = __kstrlen (str);
  size_t delim_len = __kstrlen (delim);

  for (size_t i = 0; i < str_len; ++i)
  {
    bool is_proper_delim = false;

    for (size_t j = 0; j < delim_len; ++j)
    {
      if (str[i] == delim[j])
      {
        if (token_end - token_start == 0)
        {
          ++token_start;
          break;
        }

        is_proper_delim = true;
      }
    }

    ++token_end;
    if (is_proper_delim && token_end > 0)
    {
      --token_end;
      break;
    }
  }

  if (str[token_start] == 0)
  {
    *saved_str = (char *)0;
    return (char *)0;
  }

  if (token_end == 0)
  {
    *saved_str = (char *)0;
    return &str[token_start];
  }

  if (str[token_end] == 0)
    *saved_str = &str[token_end];
  else
    *saved_str = &str[token_end + 1];

  str[token_end] = 0;
  return &str[token_start];
}

char *
__kstrtok (char *str, const char *delim)
{
  static char *saved_str;
  return __kstrtok_r (str, delim, &saved_str);
}

int
__kstrcoll (const char *str1, const char *str2)
{
  return __kstrcmp (str1, str2);
}

size_t
__kstrxfrm (char *dst, const char *src, size_t n)
{
  size_t i;
  for (i = 0; i < n && src[i] != 0; ++i)
    dst[i] = src[i];
  for (; i < n; ++i)
    dst[i] = 0;
  return i;
}

char *
__kstrsep (char **str, const char *delim)
{
  if (*str == (char *)0)
    return (char *)0;

  char *begin = *str;
  char *end = begin + __kstrcspn (begin, delim);
  if (*end)
  {
    *end = 0;
    *str = ++end;
  }
  else
  {
    *str = (char *)0;
  }
  return begin;
}

int
__kstrcmp (const char *str1, const char *str2)
{
  while (*str1 == *str2++)
    if (*str1++ == 0)
      return 0;
  return *(unsigned const char *)str1 - *(unsigned const char *)--str2;
}

int
__kstrncmp (const char *str1, const char *str2, size_t n)
{
  if (!n)
    return 0;
  do
  {
    if (*str1 != *str2++)
      return *(unsigned const char *)str1 - *(unsigned const char *)--str2;
    if (*str1++ == 0)
      break;
  } while (--n);
  return 0;
}

int
__kmemcmp (const void *blk1, const void *blk2, size_t n)
{
  const uint8_t *b1 = (const uint8_t *)blk1;
  const uint8_t *b2 = (const uint8_t *)blk2;
  while (n-- > 0)
  {
    if (*b1++ != *b2++)
      return b1[-1] < b2[-1] ? -1 : 1;
  }
  return 0;
}

void *
__kmemcpy (void *dst, const void *src, size_t n)
{
  void *orig_dst = dst;

  if (n >= sizeof(size_t) && 
      !((size_t)dst & (sizeof(size_t)-1)) && 
      !((size_t)src & (sizeof(size_t)-1))) {
    size_t *dstw = dst;
    const size_t *srcw = src;
    for (; n >= sizeof(size_t); n -= sizeof(size_t))
      *dstw++ = *srcw++;
    dst = dstw;
    src = srcw;
  }

  uint8_t *d = dst;
  const uint8_t *s = src;
  while (n--)
    *d++ = *s++;

  return orig_dst;
}

void *
__kmemccpy (void *dst, const void *src, int c, size_t n)
{
  uint8_t *pd = (uint8_t *)dst;
  const uint8_t *ps = (const uint8_t *)ps;
  for (; n--; pd++, ps++)
  {
    *pd = *ps;
    if (*pd == (uint8_t)c)
      return pd + 1;
  }
  return (void *)0;
}

void *
__kmemmove (void *dst, const void *src, int n)
{
  if (dst < src)
    return __kmemcpy (dst, src, n);
  if (((size_t)dst - (size_t)src) >= n)
    return __kmemcpy (dst, src, n);

  uint8_t *pd = (uint8_t *)dst;
  const uint8_t *ps = (const uint8_t *)src;
  for (pd += n, ps += n; n--;)
    *--pd = *--ps;
  return dst;
}

void *
__kmemset (void *blk, int c, int n)
{
  uint8_t *pd = (uint8_t *)blk;
  for (; n--;)
    *pd++ = c;
  return blk;
}

size_t
__kstrnlen(const char *str, size_t maxlen) {
    const char *char_ptr;
    for (char_ptr = str; maxlen > 0 && *char_ptr != '\0'; --maxlen)
        ++char_ptr;
    return char_ptr - str;
}
