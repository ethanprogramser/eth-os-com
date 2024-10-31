#include "kernel/keyboard.h"
#include "kernel/idt.h"
#include "kernel/keycodes.h"
#include "kernel/layout_mappings.h"
#include "kernel/util.h"
#include "klib/kdef.h"
#include "klib/kmemory.h"

#include "klib/kio.h"

#define __K_KEYBOARD_MAX_KEYCODES 0xFF

struct KeyboardState
{
  enum Keycode keycodes[__K_KEYBOARD_MAX_KEYCODES];
  size_t keycode_index;
};

static struct KeyboardState keyboard_state = { 0 };

static void __keyboard_add_to_keycode_list (enum Keycode keycode);

static bool printable_keycodes[0xFF] = {
  // 0x00 (reserved)
  0,

  // 0x01-0x04
  1, 1, 1, 0,

  // 0x05-0x0F
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

  // 0x10-0x19
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

  // 0x1A-0x1F (reserved)
  0, 0, 0, 0, 0, 0,

  // 0x20-0x39
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

  // 0x3A-0x3F (reserved)
  0, 0, 0, 0, 0, 0,

  // 0x40-0x42
  0, 1, 0,

  // 0x43-0x4F (reserved)
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  // 0x50-0x5B
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  // 0x5C
  0,

  // 0x5D-0x5F (reserved)
  0, 0, 0,

  // 0x60-0x63
  0, 0, 0, 0,

  // 0x64-0x6F (reserved)
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  // 0x70-0x71
  0, 0,

  // 0x72-0x75
  0, 0, 0, 0,

  // 0x76-0x7F (reserved)
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

  // 0x80-0x87
  0, 0, 0, 0, 0, 0, 0, 0
};

void
keyboard_init (void)
{
  __kmemset (&keyboard_state, 0, sizeof (struct KeyboardState));
  irq_install_handler (1, keyboard_handler);
}

void
keyboard_handler (struct InterruptRegisters *regs)
{
  enum Scancode scancode = inPortB (0x60) & 0x7F;
  bool pressed = (inPortB (0x60) & 0x80) == 0;

  if (pressed)
  {
    enum Keycode keycode
        = scancode_to_keycode (scancode, LAYOUT_MAPPING_QWERTY);
    __keyboard_add_to_keycode_list (keycode);
  }
}

void
keyboard_for_each_key (void (*func) (enum Keycode, void *), void *data)
{
  for (size_t i = 0; i < keyboard_state.keycode_index; ++i)
  {
    func (keyboard_state.keycodes[i], data);
    keyboard_state.keycodes[i] = 0;
  }
}

static void
__keyboard_add_to_keycode_list (enum Keycode keycode)
{
  keyboard_state.keycodes[keyboard_state.keycode_index++] = keycode;
}
