#include "kernel/util.h"
#include "klib/kint.h"

void
out_port_b (uint16_t Port, uint8_t Value)
{
  __asm__ ("outb %1, %0\n" : : "dN"(Port), "a"(Value));
}

uint8_t
in_port_b (uint16_t port)
{
  char rv;
  __asm__ ("inb %1, %0\n" : "=a"(rv) : "dN"(port));
  return rv;
}

void
out_port_w (uint16_t port, uint16_t value)
{
  __asm__ ("outw %0, %1\n" : : "a"(value), "Nd"(port));
}

uint16_t
in_port_w (uint16_t port)
{
  uint16_t ret;
  __asm__ ("inw %1, %0\n" : "=a"(ret) : "Nd"(port));
  return ret;
}
