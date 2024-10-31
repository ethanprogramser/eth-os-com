#include "kernel/kernel_shell.h"
#include "kernel/keyboard.h"
#include "kernel/keycodes.h"
#include "kernel/vga.h"
#include "klib/kio.h"
#include "klib/kmemory.h"

enum KernelShellStatus
{
  KERNEL_SHELL_STATUS_WAITING = 0,
  KERNEL_SHELL_STATUS_SUBMITTED = 1,
  KERNEL_SHELL_STATUS_QUIT = 2,
};

struct KernelShellState
{
  char line_text[0xFF];
  uint8_t position;
  bool caps;
  enum KernelShellStatus status;
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
        0, 0, 0,

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

static const char keycode_mapping_shifted[0xFF]
    = { 0,

        // 0x01-0x04
        '\b', ' ', '\t', 0,

        // 0x05-0x0F
        '~', '_', '+', '|', '{', '}', ':', '"', '<', '>', '?',

        // 0x10-0x19
        ')', '!', '@', '#', '$', '%', '^', '&', '*', '(',

        // 0x1A-0x1F (reserved)
        0, 0, 0, 0, 0, 0,

        // 0x20-0x39
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',

        // 0x3A-0x3F (reserved)
        0, 0, 0, 0, 0, 0,

        // 0x40-0x42
        0, 0, 0,

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
void __kernel_shell_handle_key (enum Keycode keycode, void *data);

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
  kernel_shell_state.status = KERNEL_SHELL_STATUS_WAITING;

  while (kernel_shell_state.status != KERNEL_SHELL_STATUS_QUIT)
  {
    switch (kernel_shell_state.status)
    {
    case KERNEL_SHELL_STATUS_WAITING:
    {
      keyboard_for_each_key (__kernel_shell_handle_key, &kernel_shell_state);
    }
    break;

    case KERNEL_SHELL_STATUS_SUBMITTED:
    {
    }
    break;

    default:
      break;
    }
  }
}

char
__kernel_shell_dispatch_keycode (enum Keycode keycode, bool shifted)
{
  return shifted ? keycode_mapping_shifted[keycode]
                 : keycode_mapping_normal[keycode];
}

void
__kernel_shell_handle_key (enum Keycode keycode, void *data)
{
  struct KernelShellState *state = (struct KernelShellState *)data;

  char c = __kernel_shell_dispatch_keycode (keycode, false);
  if (c <= 0)
  {
    switch (keycode)
    {
    case KEYCODE_CAPS:
    {
      state->caps = !state->caps;
    }
    break;

    default:
      break;
    }
  }
  else
  {
    c = state->caps ? c ^ 0x20 : c;

    if (state->position < 0xFF)
    {
      state->line_text[state->position++] = c;
      __kputc (c);
    }
    else
    {
      __kputs ("\nYou have entered maximum of 255 characters.\n");
    }
  }
}
