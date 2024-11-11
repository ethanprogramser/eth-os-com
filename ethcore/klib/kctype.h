#ifndef __K_KLIB_CTYPE_H__
#define __K_KLIB_CTYPE_H__

#define _U 01
#define _L 02
#define _N 04
#define _S 010
#define _P 020
#define _C 040
#define _X 0100
#define _B 0200

extern const char __k_ctype__[256 + 1];

static inline int
__kisalnum (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_U | _L | _N);
}

static inline int
__kisalpha (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_U | _L);
}

static inline int
__kisascii (int c)
{
  return c <= 127;
}

static inline int
__kisblank (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_B) || (c == '\t');
}

static inline int
__kiscntrl (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_C);
}

static inline int
__kisdigit (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_N);
}

static inline int
__kisgraph (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_P | _U | _L | _N);
}

static inline int
__kislower (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_L);
}

static inline int
__kisprint (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_P | _U | _L | _N | _B);
}

static inline int
__kispunct (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_P);
}

static inline int
__kisspace (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_S);
}

static inline int
__kisupper (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_U);
}

static inline int
__kisxdigit (int c)
{
  return __k_ctype__[(unsigned char)(c) + 1] & (_N | _X);
}

static inline int
__ktoascii (int c)
{
  return c & 127;
}

static inline int
__ktoupper (int c)
{
  if (c >= 'a' && c <= 'z')
    return c & ~0x20;
  return c;
}

static inline int
__ktolower (int c)
{
  if (c >= 'A' && c <= 'Z')
    return c | 0x20;
  return c;
}

static inline int
__ktoggle (int c)
{
  if (__kisalpha (c))
    return c ^ 0x20;
  return c;
}

#endif // __K_KLIB_CTYPE_H__
