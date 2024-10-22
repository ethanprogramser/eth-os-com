#ifndef __K_TIMER_H__
#define __K_TIMER_H__

struct InterruptRegisters;

void initTimer ();
void onIrq0 (struct InterruptRegisters *regs);

#endif // __K_TIMER_H__
