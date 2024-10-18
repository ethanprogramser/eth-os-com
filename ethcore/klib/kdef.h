#ifndef __K_KLIB_DEF_H__
#define __K_KLIB_DEF_H__

#include "klib/kint.h"
#include "klib/kwchar.h"

#define NULL 0

#define offsetof(st, m) ((size_t)(&((st *)0)->m))

/* NOTE: if kernel is gonna migrate to 64-bit version, you need to change these
 * macros.
 */
typedef uint32_t size_t;
typedef int32_t ssize_t;
typedef int32_t ptrdiff_t;

#endif // __K_KLIB_DEF_H__
