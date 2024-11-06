#include "kernel/keyboard.h"
#include "kernel/idt.h"
#include "kernel/keycodes.h"
#include "kernel/layout_mappings.h"
#include "kernel/util.h"
#include "klib/kdef.h"
#include "klib/kmemory.h"

#include "klib/kio.h"

#define __K_KEYBOARD_MAX_EVENTS 0xFF

#define KEYBOARD_BUFFER_SIZE 32

struct KeyboardState
{
  struct KeyboardEvent events[__K_KEYBOARD_MAX_EVENTS];
  size_t event_index;
};

struct KeyboardBuffer {
    struct KeyboardEvent events[KEYBOARD_BUFFER_SIZE];
    size_t read_pos;
    size_t write_pos;
    size_t count;
};

static struct KeyboardState keyboard_state = { 0 };
static struct KeyboardBuffer kb_buffer = {0};

static void __keyboard_add_event_to_list (struct KeyboardEvent *);

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
keyboard_for_each_event (void (*func) (struct KeyboardEvent *, void *),
                         void *data)
{
  for (size_t i = 0; i < keyboard_state.event_index; ++i)
  {
    func (&keyboard_state.events[i], data);
    __kmemset (&keyboard_state.events[i], 0, sizeof (struct KeyboardEvent));
  }
}

static void
__keyboard_add_event_to_list (struct KeyboardEvent *event)
{
  keyboard_state.events[keyboard_state.event_index++] = *event;
}

static void
keyboard_buffer_push(struct KeyboardEvent *event) {
    if (kb_buffer.count >= KEYBOARD_BUFFER_SIZE)
        return; // Buffer full
        
    kb_buffer.events[kb_buffer.write_pos] = *event;
    kb_buffer.write_pos = (kb_buffer.write_pos + 1) % KEYBOARD_BUFFER_SIZE;
    kb_buffer.count++;
}

static bool
keyboard_buffer_pop(struct KeyboardEvent *event) {
    if (kb_buffer.count == 0)
        return false;
        
    *event = kb_buffer.events[kb_buffer.read_pos];
    kb_buffer.read_pos = (kb_buffer.read_pos + 1) % KEYBOARD_BUFFER_SIZE;
    kb_buffer.count--;
    return true;
}
