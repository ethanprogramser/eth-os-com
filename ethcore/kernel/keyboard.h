#ifndef __K_KEYBOARD_H__
#define __K_KEYBOARD_H__

#include "kernel/keycodes.h"
#include "klib/kbool.h"

struct InterruptRegisters;

void keyboard_init (void);
void keyboard_handler (struct InterruptRegisters *);
enum Keycode keyboard_get_key (void);

#endif // __K_KEYBOARD_H__
