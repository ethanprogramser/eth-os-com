#include "kernel/timer.h"
#include "kernel/idt.h"
#include "kernel/util.h"
#include "klib/kint.h"

uint64_t ticks;
const uint32_t freq = 100;

void
__irq0_handler (struct InterruptRegisters *regs)
{
  ticks++;
}

void
timer_init (void)
{
  ticks = 0;
  irq_install_handler (0, &__irq0_handler);

  // 119318.16666 Mhz
  uint32_t divisor = 1193180 / freq;

  // 0011 0110
  out_port_b (0x43, 0x36);
  out_port_b (0x40, (uint8_t)(divisor & 0xFF));
  out_port_b (0x40, (uint8_t)((divisor >> 8) & 0xFF));
}
