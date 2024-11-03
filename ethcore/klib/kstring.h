#ifndef __K_KLIB_STRING_H__
#define __K_KLIB_STRING_H__

int __kstrlen (const char *str);
void __kstrcpy (char *dst, const char *src);
void __kstrncpy (char *dst, const char *src, int n);
int __kstrcmp (const char *str1, const char *str2);
#define __kstreq(str1, str2) (__kstrcmp ((str1), (str2)) == 0)

#endif // __K_KLIB_STRING_H__
