#include "kernel/keyboard.h"
#include "kernel/idt.h"
#include "kernel/keycodes.h"
#include "kernel/layout_mappings.h"
#include "kernel/util.h"
#include "klib/kmemory.h"

#include "klib/kio.h"

static enum Keycode current_key;

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
  current_key = 0;
  irq_install_handler (1, keyboard_handler);
}

void
keyboard_handler (struct InterruptRegisters *regs)
{
  enum Scancode scancode = inPortB (0x60) & 0x7F;
  bool pressed = (inPortB (0x60) & 0x80) == 0;

  enum Keycode keycode = scancode_to_keycode (scancode, LAYOUT_MAPPING_QWERTY);

  current_key = pressed ? keycode : 0;
}

enum Keycode
keyboard_get_key (void)
{
  return current_key;
}
