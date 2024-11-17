#include "kernel/kernel_shell_cmds.h"
#include "kernel/info.h"
#include "kernel/keyboard.h"
#include "kernel/keycodes.h"
#include "kernel/layout_mappings.h"
#include "kernel/vga.h"
#include "kernel_shell_cmds.h"
#include "klib/kio.h"
#include "klib/kstring.h"

static const char *ksh_help_output
    = { "List of all available commands\n"
        "* help -- Display this message\n"
        "* info -- Display information about the kernel\n"
        "* clear -- Clear screen\n"
        "* echo [string] -- Output string to the screen\n"
        "* loadkeys [keymap] -- Load a specific keymap (check `listkeys')\n"
        "* listkeys -- List all the available keymaps\n"
        "\n" };

void
ksh_help (const char *args)
{
  __kputs (ksh_help_output);
}

void
ksh_info (const char *args)
{
  __kputs (__K_KERNEL_NAME);
  __kputc (' ');

  __kputs (__K_KERNEL_VERSION);
  __kputc (' ');

  __kputs (__K_ARCHITECTURE);
  __kputc ('\n');
}

void
ksh_clear (const char *args)
{
  vga_clear_screen ();
}

void
ksh_echo (const char *text)
{
  __kputs (text);
  __kputc ('\n');
}

void
ksh_loadkeys (const char *args)
{
  for (size_t i = 0; i < MAX_LAYOUT_TABLE_ENTRIES; i++)
  {
    size_t map_str_len = __kstrlen (layout_map_table[i].map_name);
    if (__kstrneq (args, layout_map_table[i].map_name, map_str_len))
    {
      keyboard_set_layout (layout_map_table[i].mapping_value);
      __kputs ("Success\n");
      return;
    }
  }

  __kputs ("Unknown keymap\n");
}

void
ksh_listkeys (const char *args)
{
  static const char entry_prefix[4] = " * ";
  __kputs ("List of keymaps:\n");
  for (size_t i = 0; i < MAX_LAYOUT_TABLE_ENTRIES; i++)
  {
    __kputs (entry_prefix);
    __kputs (layout_map_table[i].map_name);
    __kputc ('\n');
  }
  __kputc ('\n');
}
