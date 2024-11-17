#ifndef __K_KEYBOARD_H__
#define __K_KEYBOARD_H__

#include "kernel/keycodes.h"
#include "kernel/layout_mappings.h"
#include "klib/kbool.h"

struct InterruptRegisters;

enum KeyboardEventType
{
  KEYBOARD_EVENT_TYPE_INVALID = 0,
  KEYBOARD_EVENT_TYPE_PRESSED = 1,
  KEYBOARD_EVENT_TYPE_RELEASED = 2,
};

struct KeyboardEvent
{
  enum Keycode keycode;
  enum KeyboardEventType event_type;
};

typedef void (*KeyboardEventHandler) (struct KeyboardEvent *, void *);

void keyboard_init (void);
void keyboard_handler (struct InterruptRegisters *);
void keyboard_for_each_event (KeyboardEventHandler, void *data);
void keyboard_set_layout (enum LayoutMapping);
enum LayoutMapping keyboard_get_layout (void);

#endif // __K_KEYBOARD_H__
