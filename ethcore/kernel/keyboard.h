#ifndef __K_KEYBOARD_H__
#define __K_KEYBOARD_H__

#include "kernel/keycodes.h"
#include "klib/kbool.h"

struct InterruptRegisters;

enum KeyboardEventType
{
  KEYBOARD_EVENT_TYPE_PRESSED = 0,
  KEYBOARD_EVENT_TYPE_RELEASED = 1,
};

struct KeyboardEvent
{
  enum Keycode keycode;
  enum KeyboardEventType event_type;
};

void keyboard_init (void);
void keyboard_handler (struct InterruptRegisters *);
void keyboard_for_each_event (void (*func) (struct KeyboardEvent *, void *),
                              void *data);

#endif // __K_KEYBOARD_H__
