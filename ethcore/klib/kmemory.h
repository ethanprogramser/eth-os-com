#ifndef __K_KLIB_MEMORY_H__
#define __K_KLIB_MEMORY_H__

#include "klib/kdef.h"
#include "klib/kint.h"

void *__kmemcpy(void *dst, const void *src, size_t n);
void *__kmemset(void *blk, int c, size_t n);

#endif // __K_KLIB_MEMORY_H__
