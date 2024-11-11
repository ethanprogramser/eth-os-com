#include "kernel/keyboard.h"
#include "kernel/idt.h"
#include "kernel/keycodes.h"
#include "kernel/layout_mappings.h"
#include "kernel/util.h"
#include "klib/kdef.h"
#include "klib/kmemory.h"

#include "klib/kio.h"

#define __K_KEYBOARD_MAX_EVENTS 0xFF

struct KeyboardState
{
  struct KeyboardEvent events[__K_KEYBOARD_MAX_EVENTS];
  size_t event_index;
};

static struct KeyboardState keyboard_state = { 0 };

static inline void __keyboard_add_event_to_list (struct KeyboardEvent *);

void
keyboard_init (void)
{
  __kmemset (&keyboard_state, 0, sizeof (struct KeyboardState));
  irq_install_handler (1, keyboard_handler);
}

void
keyboard_handler (struct InterruptRegisters *regs)
{
  uint8_t data = in_port_b (0x60);

  enum Scancode scancode = data & 0x7F;
  enum KeyboardEventType type = (data & 0x80) == 0
                                    ? KEYBOARD_EVENT_TYPE_PRESSED
                                    : KEYBOARD_EVENT_TYPE_RELEASED;
  enum Keycode keycode = scancode_to_keycode (scancode, LAYOUT_MAPPING_QWERTY);
  __keyboard_add_event_to_list (&(struct KeyboardEvent){
      .keycode = keycode,
      .event_type = type,
  });
}

void
keyboard_for_each_event (KeyboardEventHandler handler, void *data)
{
  if (keyboard_state.event_index > 0)
  {
    for (size_t i = 0; i < keyboard_state.event_index; ++i)
      handler (&keyboard_state.events[i], data);
    __kmemset (keyboard_state.events, 0,
               sizeof (struct KeyboardEvent) * keyboard_state.event_index);
    keyboard_state.event_index = 0;
  }
}

static inline void
__keyboard_add_event_to_list (struct KeyboardEvent *event)
{
  keyboard_state.events[keyboard_state.event_index] = *event;
  if (keyboard_state.event_index <= __K_KEYBOARD_MAX_EVENTS)
    keyboard_state.event_index++;
}
