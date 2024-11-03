#ifndef __K_STRING_UTILS_H__
#define __K_STRING_UTILS_H__

#include "klib/kdef.h"
#include "klib/kint.h"

char *string_trim (char *str);
void string_mid (char *dst, const char *src, size_t start, size_t len);
size_t string_index (const char *str, char c);
char *string_empty (char *str);

#endif // __K_STRING_UTILS_H__
