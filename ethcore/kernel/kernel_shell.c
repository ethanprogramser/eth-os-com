#include "kernel/kernel_shell.h"
#include "kernel/keyboard.h"
#include "kernel/keycodes.h"
#include "kernel/vga.h"
#include "klib/kio.h"
#include "klib/kmemory.h"

struct KernelShellState
{
  char line_text[0x100];
  uint8_t position;
  bool caps;
};

static struct KernelShellState kernel_shell_state = { 0 };

static const char *prefix = "shell>";

static const char keycode_mapping_normal[0xFF]
    = { 0,

        // 0x01-0x04
        '\b', ' ', '\t', 0,

        // 0x05-0x0F
        '`', '-', '=', '\\', '[', ']', ';', '\'', ',', '.', '/',

        // 0x10-0x19
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',

        // 0x1A-0x1F (reserved)
        0, 0, 0, 0, 0, 0,

        // 0x20-0x39
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',

        // 0x3A-0x3F (reserved)
        0, 0, 0, 0, 0, 0,

        // 0x40-0x42
        0, '\n', 0,

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
        0, 0, 0, 0, 0, 0, 0, 0 };

char __kernel_shell_dispatch_keycode (enum Keycode keycode, bool shifted);

void
kernel_shell_init (void)
{
  vga_set_color (VGA_COLOR_BLACK, VGA_COLOR_WHITE);
  vga_clear_screen ();

  __kputs ("Welcome to Kernel Shell.\n\n");
  __kmemset (&kernel_shell_state, 0, sizeof (struct KernelShellState));
}

void
kernel_shell_loop (void)
{
  vga_enable_cursor ();

  enum Keycode key = 0;
  while (1)
  {
    key = keyboard_get_last_key ();
    if (!keyboard_was_key_pressed (key) && keyboard_is_key_pressed (key))
    {
      // bool shift_pressed = keyboard_is_key_pressed (KEYCODE_LSHIFT)
      //                      || keyboard_is_key_pressed (KEYCODE_RSHIFT);
      char c = __kernel_shell_dispatch_keycode (key, false);

      if (c != 0 && kernel_shell_state.position < 0xFF)
      {
        kernel_shell_state.line_text[kernel_shell_state.position] = c;
        __kputc (c);
        kernel_shell_state.position++;
        continue;
      }
    }
  }
}

char
__kernel_shell_dispatch_keycode (enum Keycode keycode, bool shifted)
{
  return keycode_mapping_normal[keycode];
}
