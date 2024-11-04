#include "kernel/util.h"
#include "klib/kint.h"

void
out_port_b (uint16_t Port, uint8_t Value)
{
  asm volatile ("outb %1, %0" : : "dN"(Port), "a"(Value));
}

char
in_port_b (uint16_t port)
{
  char rv;
  asm volatile ("inb %1, %0" : "=a"(rv) : "dN"(port));
  return rv;
}

void 
outPortW(uint16_t port, uint16_t value) {
    __asm__ volatile (
        "outw %0, %1"
        :
        : "a"(value), "Nd"(port)
    );
}

uint16_t
inPortW(uint16_t port) {
    uint16_t ret;
      __asm__ volatile (
          "inw %1, %0"
          : "=a"(ret)
          : "Nd"(port)
      );
    return ret;
}
