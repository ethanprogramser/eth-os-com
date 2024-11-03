#ifndef __K_KLIB_STRING_H__
#define __K_KLIB_STRING_H__

#include "klib/kdef.h"

size_t __kstrspn (const char *str, const char *accept);
size_t __kstrcspn (const char *str, const char *reject);
size_t __kstrlen (const char *str);
size_t __kstrnlen (const char *str, size_t max_len);
char *__kstrcpy (char *dst, const char *src);
char *__kstpcpy (char *dst, const char *src);
char *__kstrncpy (char *dst, const char *src, size_t n);
size_t __kstrlcpy (char *dst, const char *src, size_t n);
char *__kstrchr (const char *str, int c);
char *__kindex (const char *str, int c);
char *__kstrchrnul (const char *str, int c);
void *__kmemchr (const void *ptr, int c, size_t sz);
char *__kstrrchr (const char *str, int c);
char *__krindex (const char *str, int c);
char *__kstrcat (char *dst, const char *src);
char *__kstrncat (char *dst, const char *src, size_t n);
char *__kstrstr (const char *hay, const char *needle);
char *__kstrcasestr (const char *hay, const char *needle);
char *__kstrpbrk (const char *str, const char *accept);
char *__kstrtok_r (char *str, const char *delim, char **saved_str);
char *__kstrtok (char *str, const char *delim);
int __kstrcoll (const char *str1, const char *str2);
size_t __kstrxfrm (char *dst, const char *src, size_t n);
char *__kstrsep (char **str, const char *delim);
int __kstrcmp (const char *str1, const char *str2);
#define __kstreq(str1, str2) (__kstrcmp ((str1), (str2)) == 0)
int __kstrncmp (const char *str1, const char *str2, size_t n);
#define __kstrneq(str1, str2) (__kstrncmp ((str1), (str2), (n)) == 0)
int __kmemcmp (const void *blk1, const void *blk2, size_t n);
void *__kmemcpy (void *dst, const void *src, size_t n);
void *__kmemccpy (void *dst, const void *src, int c, size_t n);
void *__kmemmove (void *dst, const void *src, int n);
void *__kmemset (void *blk, int c, int n);

#endif // __K_KLIB_STRING_H__
