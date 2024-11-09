#include "kernel/kernel_shell.h"
#include "kernel/kernel_shell_cmds.h"
#include "kernel/keyboard.h"
#include "kernel/keycodes.h"
#include "kernel/util.h"
#include "kernel/vga.h"
#include "klib/kctype.h"
#include "klib/kdef.h"
#include "klib/kio.h"
#include "klib/kstring.h"

// WARNING: When `MAX_LINE_LENGTH` is 0x100 (256) (or maybe is power of 2),
// strange glitches may occur when pressing backspace at last position.
#define MAX_LINE_LENGTH (0xFFul)
#define MAX_CMDS (0x7Ful)

enum KernelShellStatus
{
  KERNEL_SHELL_STATUS_WAITING = 0,
  KERNEL_SHELL_STATUS_SUBMITTED = 1,
  KERNEL_SHELL_STATUS_QUIT = 2,
};

struct KernelShellState
{
  char line_text[MAX_LINE_LENGTH];
  size_t position;
  bool caps;
  uint8_t shifts_pressed;
  enum KernelShellStatus status;
  bool wait_for_control_code;
};

static struct KernelShellState kernel_shell_state = { 0 };

static const char *prefix = "ksh> ";

static const struct KernelShellCMD cmds[MAX_CMDS] = {
  { ksh_clear, "clear" },
  { ksh_help, "help" },
  { ksh_info, "info" },
  { ksh_echo, "echo" },
};

static const char keycode_mapping_normal[0xFF]
    = { 0,

        // 0x01-0x04
        0, ' ', 0, 0,

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
        0, ' ', 0, 0,

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

static char __kernel_shell_translate_keycode (enum Keycode keycode,
                                              bool shifted);
static void __kernel_shell_handle_event (struct KeyboardEvent *event,
                                         void *data);
static void __kernel_shell_handle_command (struct KernelShellState *state,
                                           const char *cmd);
static void __kernel_shell_print_control_code (char c);

void
kernel_shell_init (void)
{
  vga_reset ();
  vga_set_color (VGA_COLOR (VGA_COLOR_BLACK, VGA_COLOR_WHITE));
  vga_clear_screen ();

  __kputs ("Welcome to Eth-OS Kernel Shell.\n\n");
  __kmemset (&kernel_shell_state, 0, sizeof (struct KernelShellState));
}

void
kernel_shell_loop (void)
{
  vga_enable_cursor ();
  kernel_shell_state.status = KERNEL_SHELL_STATUS_WAITING;

  __kputs (prefix);

  while (kernel_shell_state.status != KERNEL_SHELL_STATUS_QUIT)
  {
    switch (kernel_shell_state.status)
    {
    case KERNEL_SHELL_STATUS_WAITING:
    {
      keyboard_for_each_event (__kernel_shell_handle_event,
                               &kernel_shell_state);
    }
    break;

    case KERNEL_SHELL_STATUS_SUBMITTED:
    {
      if ((uint8_t)kernel_shell_state.line_text[0] > 0)
      {
        // TODO: Add command to the command buffer.
        __kernel_shell_handle_command (
            &kernel_shell_state, (const char *)kernel_shell_state.line_text);
      }

      __kputs (prefix);
      kernel_shell_state.status = KERNEL_SHELL_STATUS_WAITING;

      __kmemset (kernel_shell_state.line_text, 0,
                 sizeof (kernel_shell_state.line_text));
      kernel_shell_state.position = 0;
    }
    break;

    default:
      break;
    }
  }
}

static char
__kernel_shell_translate_keycode (enum Keycode keycode, bool shifted)
{
  return shifted ? keycode_mapping_shifted[keycode]
                 : keycode_mapping_normal[keycode];
}

static void
__kernel_shell_handle_event (struct KeyboardEvent *event, void *data)
{
  struct KernelShellState *state = (struct KernelShellState *)data;

  switch (event->event_type)
  {
  case KEYBOARD_EVENT_TYPE_PRESSED:
  {
    char c = __kernel_shell_translate_keycode (event->keycode,
                                               state->shifts_pressed > 0);
    if (c <= 0)
    {
      switch (event->keycode)
      {
      case KEYCODE_CAPS:
      {
        state->caps = !state->caps;
      }
      break;

      case KEYCODE_LSHIFT:
      case KEYCODE_RSHIFT:
      {
        state->shifts_pressed++;
      }
      break;

      case KEYCODE_BACKSPACE:
      {
        if (state->position > 0)
        {
          state->line_text[state->position--] = 0;
          __kputc ('\b');
        }
      }
      break;

      case KEYCODE_RETURN:
      {
        __kputc ('\n');
        state->status = KERNEL_SHELL_STATUS_SUBMITTED;
      }
      break;

      case KEYCODE_LCONTROL:
      case KEYCODE_RCONTROL:
      {
        state->wait_for_control_code = true;
      }
      break;

      case KEYCODE_TAB:
      {
        if (state->position < MAX_LINE_LENGTH)
        {
          size_t size = clamp (MAX_LINE_LENGTH - state->position, 0, 4);
          char tab[5] = { 0 };
          __kmemset (tab, ' ', size);
          __kmemset ((void *)(state->line_text + state->position), ' ', size);
          __kputs (tab);
          state->position += size;
        }
      }
      break;

      default:
        break;
      }
    }
    else
    {
      if (state->wait_for_control_code)
      {
        char control_code_output[3] = { 0 };
        char c = __kernel_shell_translate_keycode (event->keycode, true);
        c = __kisalpha (c) ? c : 0;

        switch (event->keycode)
        {
        case KEYCODE_L:
        {
          __kernel_shell_print_control_code (c);
          ksh_clear (0);
          __kputs (prefix);
        }
        break;

        case KEYCODE_C:
        {
          __kernel_shell_print_control_code (c);
          state->status = KERNEL_SHELL_STATUS_SUBMITTED;
          __kmemset (state->line_text, 0, MAX_LINE_LENGTH);
          state->position = 0;
          __kputc ('\n');
        }
        break;

        default:
          break;
        }
      }
      else
      {
        c = state->caps ? __ktoggle (c) : c;

        if (state->position < MAX_LINE_LENGTH)
        {
          state->line_text[state->position++] = c;
          __kputc (c);
        }
        else
        {
          __kputs ("\nYou have entered maximum of 255 characters.\n");

          __kputs (prefix);
          __kputs (state->line_text);
        }
      }
    }
  }
  break;

  case KEYBOARD_EVENT_TYPE_RELEASED:
  {
    switch (event->keycode)
    {
    case KEYCODE_LSHIFT:
    case KEYCODE_RSHIFT:
    {
      state->shifts_pressed--;
    }
    break;

    case KEYCODE_LCONTROL:
    case KEYCODE_RCONTROL:
    {
      state->wait_for_control_code = false;
    }
    break;

    default:
      break;
    }
  }
  break;

  default:
    break;
  }
}

static void
__kernel_shell_handle_command (struct KernelShellState *state, const char *cmd)
{
  char trimmed[MAX_LINE_LENGTH];
  __kstrncpy (trimmed, cmd, MAX_LINE_LENGTH);
  for (size_t i = 0; i < __kstrnlen (cmd, MAX_LINE_LENGTH) && trimmed[i] != 0;
       ++i)
  {
    if (__kisspace (trimmed[i]))
    {
      trimmed[i] = 0;
      break;
    }
  }

  for (size_t i = 0; i < MAX_CMDS; ++i)
  {
    size_t cmd_len = __kstrnlen (cmds[i].cmd, MAX_LINE_LENGTH);
    if (__kstrneq (trimmed, cmds[i].cmd, cmd_len) && trimmed[cmd_len] == 0)
    {
      cmds[i].func ((const char *)(trimmed + cmd_len + 1));
      return;
    }
  }

  __kputs ("ksh: Unknown command: ");
  __kputs (cmd);
  __kputc ('\n');
}

static void
__kernel_shell_print_control_code (char c)
{
  if (c > 0)
  {
    vga_set_color (VGA_COLOR (VGA_COLOR_BLACK, VGA_COLOR_DGREY));
    __kputc ('^');
    __kputc (c);
    vga_set_color (VGA_COLOR (VGA_COLOR_BLACK, VGA_COLOR_WHITE));
  }
}
