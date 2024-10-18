#ifndef __K_KLIB_INT_H__
#define __K_KLIB_INT_H__

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long int uint64_t;

typedef signed char int8_t;
typedef signed short int16_t;
typedef signed int int32_t;
typedef signed long long int int64_t;

typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;
typedef int64_t int_least64_t;

/* NOTE: if kernel is gonna migrate to 64-bit version, you need to change these
 * macros.
 */
#define __K_FAST_INT int32_t
#define __K_FAST_UINT uint32_t

typedef __K_FAST_UINT uint_fast8_t;
typedef __K_FAST_UINT uint_fast16_t;
typedef __K_FAST_UINT uint_fast32_t;
typedef uint64_t uint_fast64_t;

typedef __K_FAST_INT int_fast8_t;
typedef __K_FAST_INT int_fast16_t;
typedef __K_FAST_INT int_fast32_t;
typedef int64_t int_fast64_t;

#define INT8_MIN ((int8_t)-128)
#define INT8_MAX ((int8_t)127)
#define UINT8_MAX ((uint8_t)255)
#define INT16_MIN ((int16_t)0x8000)
#define INT16_MAX ((int16_t)0x7FFF)
#define UINT16_MAX ((uint16_t)0xFFFF)
#define INT32_MIN ((int32_t)0x80000000)
#define INT32_MAX ((int32_t)0x7FFFFFFF)
#define UINT32_MAX ((uint32_t)0xFFFFFFFF)
#define INT64_MIN ((int64_t)0x8000000000000000)
#define INT64_MAX ((int64_t)0x7FFFFFFFFFFFFFFF)
#define UINT64_MAX ((uint64_t)0xFFFFFFFFFFFFFFFF)

#define INT_LEAST8_MIN INT8_MIN
#define INT_LEAST8_MAX INT8_MAX
#define UINT_LEAST8_MAX UINT8_MAX
#define INT_LEAST16_MIN INT16_MIN
#define INT_LEAST16_MAX INT16_MAX
#define UINT_LEAST16_MAX UINT16_MAX
#define INT_LEAST32_MIN INT32_MIN
#define INT_LEAST32_MAX INT32_MAX
#define UINT_LEAST32_MAX UINT32_MAX
#define INT_LEAST64_MIN INT64_MIN
#define INT_LEAST64_MAX INT64_MAX
#define UINT_LEAST64_MAX UINT64_MAX

/* NOTE: if kernel is gonna migrate to 64-bit version, you need to change these
 * macros.
 */
#define __K_FAST_INT_MIN 0x80000000
#define __K_FAST_INT_MAX 0x7FFFFFFF
#define __K_FAST_UINT_MAX 0xFFFFFFFF

#define INT_FAST8_MIN ((int_fast8_t)__K_FAST_INT_MIN)
#define INT_FAST8_MAX ((int_fast8_t)__K_FAST_INT_MAX)
#define UINT_FAST8_MAX ((uint_fast8_t)__K_FAST_UINT_MAX)
#define INT_FAST16_MIN ((int_fast16_t)__K_FAST_INT_MIN)
#define INT_FAST16_MAX ((int_fast16_t)__K_FAST_INT_MAX)
#define UINT_FAST16_MAX ((uint_fast16_t)__K_FAST_UINT_MAX)
#define INT_FAST32_MIN ((int_fast32_t)__K_FAST_INT_MIN)
#define INT_FAST32_MAX ((int_fast32_t)__K_FAST_INT_MAX)
#define UINT_FAST32_MAX ((uint_fast32_t)__K_FAST_UINT_MAX)
#define INT_FAST64_MIN ((int_fast64_t)0x8000000000000000)
#define INT_FAST64_MAX ((int_fast64_t)0x7FFFFFFFFFFFFFFF)
#define UINT_FAST64_MAX ((uint_fast64_t)0xFFFFFFFFFFFFFFFF)

/* NOTE: if kernel is gonna migrate to 64-bit version, you need to change these
 * macros.
 * */
#define INTPTR_MIN INT32_MIN
#define INTPTR_MAX INT32_MAX
#define UINTPTR_MAX UINT32_MAX

#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#define UINTMAX_MAX UINT64_MAX

#define PTRDIFF_MIN INTPTR_MIN
#define PTRDIFF_MAX INTPTR_MAX
#define SIZE_MAX UINTPTR_MAX

#endif // __K_KLIB_INT_H__
