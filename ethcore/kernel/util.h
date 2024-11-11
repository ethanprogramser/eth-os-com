#ifndef __K_UTIL_H__
#define __K_UTIL_H__

#include "klib/kint.h"

#define __CEIL_DIV(a, b) ((((a) + (b)) - 1) / (b))

struct InterruptRegisters
{
  uint32_t cr2;
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, csm, eflags, useresp, ss;
};

static inline void
out_port_b (uint16_t Port, uint8_t Value)
{
  __asm__ ("outb %1, %0\n" : : "dN"(Port), "a"(Value));
}

static inline uint8_t
in_port_b (uint16_t port)
{
  char rv;
  __asm__ ("inb %1, %0\n" : "=a"(rv) : "dN"(port));
  return rv;
}

static inline void
out_port_w (uint16_t port, uint16_t value)
{
  __asm__ ("outw %0, %1\n" : : "a"(value), "Nd"(port));
}

static inline uint16_t
in_port_w (uint16_t port)
{
  uint16_t ret;
  __asm__ ("inw %1, %0\n" : "=a"(ret) : "Nd"(port));
  return ret;
}

static inline int_fast32_t
clamp (int_fast32_t val, int_fast32_t min, int_fast32_t max)
{
  return ((val <= min) ? min : (val >= max) ? max : val);
}

#endif // __K_UTIL_H__
