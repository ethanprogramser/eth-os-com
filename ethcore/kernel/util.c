#include "kernel/util.h"
#include "klib/kint.h"

void outPortB(uint16_t Port, uint8_t Value) {
  asm volatile("outb %1, %0" : : "dN"(Port), "a"(Value));
}

char inPortB(uint16_t port) {
  char rv;
  asm volatile("inb %1, %0" : "=a"(rv) : "dN"(port));
  return rv;
}
