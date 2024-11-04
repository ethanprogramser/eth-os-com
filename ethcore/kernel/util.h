#ifndef __K_UTIL_H__
#define __K_UTIL_H__

#include "klib/kint.h"

#define __CEIL_DIV(a, b) ((((a) + (b)) - 1) / (b))

void out_port_b (uint16_t Port, uint8_t Value);
char in_port_b (uint16_t port);
void out_port_w (uint16_t port, uint16_t value);
uint16_t in_port_w (uint16_t port);

struct InterruptRegisters
{
  uint32_t cr2;
  uint32_t ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t int_no, err_code;
  uint32_t eip, csm, eflags, useresp, ss;
};

#endif // __K_UTIL_H__
