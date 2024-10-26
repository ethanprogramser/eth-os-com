#include "klib/kio.h"
#include "klib/kint.h"

#include "kernel/vga.h"

#define PRINTF_STATE_START 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_SHORT 2
#define PRINTF_STATE_LONG 3
#define PRINTF_STATE_SPEC 4

#define PRINTF_LENGTH_START 0
#define PRINTF_LENGTH_SHORT_SHORT 1
#define PRINTF_LENGTH_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4

extern void x86_div64_32 (uint64_t, uint32_t, uint64_t *, uint32_t *);

int *__kprintf_number (int *, int, char, int);

void
__kputc (char c)
{
  vga_print (c);
}

void
__kputs (const char *s)
{
  for (; *s; s++)
    vga_print (*s);
}

void
__kprintf (const char *fmt, ...)
{
  int *argp = (int *)&fmt;
  int state = PRINTF_STATE_START;
  int length = PRINTF_LENGTH_START;
  int radix = 10;
  char sign = 0;

  argp++;
  while (*fmt)
  {
    switch (state)
    {
    case PRINTF_STATE_START:
      if (*fmt == '%')
      {
        state = PRINTF_STATE_LENGTH;
      }
      else
      {
        __kputc (*fmt);
      }
      break;
    case PRINTF_STATE_LENGTH:
      if (*fmt == 'h')
      {
        length = PRINTF_LENGTH_SHORT;
        state = PRINTF_STATE_SHORT;
      }
      else if (*fmt == 'l')
      {
        length = PRINTF_LENGTH_LONG;
        state = PRINTF_STATE_LONG;
      }
      else
      {
        goto PRINTF_STATE_SPEC_;
      }
      break;
      // hd
    case PRINTF_STATE_SHORT:
      if (*fmt == 'h')
      {
        length = PRINTF_LENGTH_SHORT_SHORT;
        state = PRINTF_STATE_SPEC;
      }
      else
      {
        goto PRINTF_STATE_SPEC_;
      }
      break;

    case PRINTF_STATE_LONG:
      if (*fmt == 'l')
      {
        length = PRINTF_LENGTH_LONG_LONG;
        state = PRINTF_STATE_SPEC;
      }
      else
      {
        goto PRINTF_STATE_SPEC_;
      }
      break;

    case PRINTF_STATE_SPEC:
    PRINTF_STATE_SPEC_:
      switch (*fmt)
      {
      case 'c':
        __kputc ((char)*argp);
        argp++;
        break;
      case 's':
        if (length == PRINTF_LENGTH_LONG || length == PRINTF_LENGTH_LONG_LONG)
        {
          __kputs (*(const char **)argp);
          argp += 2;
        }
        else
        {
          __kputs (*(const char **)argp);
          argp++;
        }
        break;
      case '%':
        __kputc ('%');
        break;
      case 'd':
      case 'i':
        radix = 10;
        sign = 1;
        argp = __kprintf_number (argp, length, sign, radix);
        break;
      case 'u':
        radix = 10;
        sign = 0;
        argp = __kprintf_number (argp, length, sign, radix);
        break;
      case 'X':
      case 'x':
      case 'p':
        radix = 16;
        sign = 0;
        argp = __kprintf_number (argp, length, sign, radix);
        break;
      case 'o':
        radix = 8;
        sign = 0;
        argp = __kprintf_number (argp, length, sign, radix);
        break;
      default:
        break;
      }
      state = PRINTF_STATE_START;
      length = PRINTF_LENGTH_START;
      radix = 10;
      sign = 0;
      break;
    }
    fmt++;
  }
}

const char possibleChars[] = "0123456789abcdef";

int *
__kprintf_number (int *argp, int length, char sign, int radix)
{
  char buffer[32] = "";
  uint32_t number;
  int number_sign = 1;
  int pos = 0;

  switch (length)
  {
  case PRINTF_LENGTH_SHORT_SHORT:
  case PRINTF_LENGTH_SHORT:
  case PRINTF_LENGTH_START:
    if (sign)
    {
      int n = *argp;
      if (n < 0)
      {
        n = -n;
        number_sign = -1;
      }
      number = (uint32_t)n;
    }
    else
    {
      number = *(uint32_t *)argp;
    }
    argp++;
    break;
  case PRINTF_LENGTH_LONG:
    if (sign)
    {
      long int n = *(long int *)argp;
      if (n < 0)
      {
        n = -n;
        number_sign = -1;
      }
      number = (uint32_t)n;
    }
    else
    {
      number = *(uint32_t *)argp;
    }
    argp += 2;
    break;
  case PRINTF_LENGTH_LONG_LONG:
    if (sign)
    {
      long long int n = *(long long int *)argp;
      if (n < 0)
      {
        n = -n;
        number_sign = -1;
      }
      number = (uint32_t)n;
    }
    else
    {
      number = *(uint32_t *)argp;
    }
    argp += 4;
    break;
  }

  do
  {
    uint32_t rem = number % radix;
    number = number / radix;

    buffer[pos++] = possibleChars[rem];
  } while (number > 0);

  if (sign && number_sign < 0)
  {
    buffer[pos++] = '-';
  }

  while (--pos >= 0)
  {
    __kputc (buffer[pos]);
  }

  return argp;
}
