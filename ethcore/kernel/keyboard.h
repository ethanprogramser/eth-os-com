#ifndef __K_KEYBOARD_H__
#define __K_KEYBOARD_H__

#include "kernel/keycodes.h"
#include "klib/kbool.h"

struct InterruptRegisters;

void keyboard_init (void);
void keyboard_handler (struct InterruptRegisters *);
void keyboard_for_each_key (void (*func) (enum Keycode, void *), void *data);

#endif // __K_KEYBOARD_H__
