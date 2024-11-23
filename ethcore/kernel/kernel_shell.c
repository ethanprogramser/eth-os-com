#include "kernel/kernel_shell.h"
#include "kernel/kernel_shell_cmds.h"
#include "kernel/keyboard.h"
#include "kernel/keycodes.h"
#include "kernel/layout_layers.h"
#include "kernel/layout_mappings.h"
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
#define MAX_BUFFER_SIZE (0x10ul)
#define DEFAULT_KSH_COLOR VGA_COLOR (VGA_COLOR_BLACK, VGA_COLOR_LGREY)

enum KernelShellStatus
{
  KERNEL_SHELL_STATUS_WAITING = 0,
  KERNEL_SHELL_STATUS_SUBMITTED = 1,
  KERNEL_SHELL_STATUS_QUIT = 2,
};

struct KernelShellState
{
  enum KernelShellStatus status;

  char line_text[MAX_LINE_LENGTH];
  size_t position;

  bool caps;
  bool wait_for_control_code;
  uint8_t shifts_pressed;

  char buffer[MAX_BUFFER_SIZE][MAX_LINE_LENGTH];
  size_t buffer_position, buffer_last;
};

static struct KernelShellState kernel_shell_state = { 0 };

static const char *prefix = "ksh> ";

static const struct KernelShellCMD cmds[MAX_CMDS] = {
  { ksh_clear, "clear" },       { ksh_help, "help" },
  { ksh_info, "info" },         { ksh_echo, "echo" },
  { ksh_loadkeys, "loadkeys" }, { ksh_listkeys, "listkeys" },
};

static inline char __kernel_shell_translate_keycode (enum Keycode keycode,
                                                     bool shifted);
static inline void __kernel_shell_handle_event (struct KeyboardEvent *event,
                                                void *data);
static inline void
__kernel_shell_handle_command (struct KernelShellState *state,
                               const char *cmd);
static inline void __kernel_shell_print_control_code (char c);
static inline void
__kernel_shell_extend_buffer (struct KernelShellState *state, const char *cmd);

void
kernel_shell_init (void)
{
  vga_reset ();
  vga_set_color (DEFAULT_KSH_COLOR);
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
      if (__kstrnlen (kernel_shell_state.line_text, MAX_LINE_LENGTH) > 0)
      {
        __kernel_shell_extend_buffer (
            &kernel_shell_state, (const char *)kernel_shell_state.line_text);
        __kernel_shell_handle_command (
            &kernel_shell_state, (const char *)kernel_shell_state.line_text);
      }

      __kputs (prefix);
      kernel_shell_state.status = KERNEL_SHELL_STATUS_WAITING;

      __kmemset (kernel_shell_state.line_text, 0,
                 sizeof (kernel_shell_state.line_text));
      kernel_shell_state.position = 0;

      kernel_shell_state.buffer_position = 0;
    }
    break;

    default:
      break;
    }
  }
}

static inline char
__kernel_shell_translate_keycode (enum Keycode keycode, bool shifted)
{
  char *layer_normal = 0;
  char *layer_shifted = 0;

  switch (keyboard_get_layout ())
  {
  case LAYOUT_MAPPING_QWERTY:
    layer_normal = (char *)qwerty_layer_normal;
    layer_shifted = (char *)qwerty_layer_shifted;
    break;

  case LAYOUT_MAPPING_AZERTY:
    layer_normal = (char *)azerty_layer_normal;
    layer_shifted = (char *)azerty_layer_shifted;
    break;

  case LAYOUT_MAPPING_DVORAK:
    // FIXME: Not implemented yet.
    break;

  default:
    break;
  }

  if (layer_normal == 0 || layer_shifted == 0)
    return 0;

  return shifted ? layer_shifted[keycode] : layer_normal[keycode];
}

static inline void
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

      case KEYCODE_UP:
      {
        size_t line_len = state->position;
        __kstrncpy (state->line_text, state->buffer[state->buffer_position],
                    MAX_LINE_LENGTH);
        state->position = __kstrnlen (state->line_text, MAX_LINE_LENGTH);
        if (state->buffer_position < state->buffer_last - 1)
          state->buffer_position++;
        else
          state->buffer_position = 0;
        for (size_t i = 0; i < line_len; ++i)
          __kputc ('\b');
        __kputs (state->line_text);
      }
      break;
      case KEYCODE_DOWN:
      {
        size_t line_len = state->position;
        if (state->buffer_position > 0)
          state->buffer_position--;
        else
          state->buffer_position = state->buffer_last - 1;
        __kstrncpy (state->line_text, state->buffer[state->buffer_position],
                    MAX_LINE_LENGTH);
        state->position = __kstrnlen (state->line_text, MAX_LINE_LENGTH);
        for (size_t i = 0; i < line_len; ++i)
          __kputc ('\b');
        __kputs (state->line_text);
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

static inline void
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

static inline void
__kernel_shell_print_control_code (char c)
{
  if (c > 0)
  {
    vga_set_color (VGA_COLOR (VGA_COLOR_BLACK, VGA_COLOR_DGREY));
    __kputc ('^');
    __kputc (c);
    vga_set_color (DEFAULT_KSH_COLOR);
  }
}

static inline void
__kernel_shell_extend_buffer (struct KernelShellState *state, const char *cmd)
{
  if (state->buffer[state->buffer_last] != 0
      && state->buffer_last < MAX_BUFFER_SIZE - 1)
    state->buffer_last++;

  for (size_t i = MAX_BUFFER_SIZE - 1; i > 0; --i)
    __kstrncpy (state->buffer[i], state->buffer[i - 1], MAX_LINE_LENGTH);

  __kstrncpy (state->buffer[0], cmd, MAX_LINE_LENGTH);
}
