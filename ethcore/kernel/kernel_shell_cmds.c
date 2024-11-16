#include "kernel/kernel_shell_cmds.h"
#include "kernel/info.h"
#include "kernel/vga.h"
#include "klib/kio.h"
#include "klib/kstring.h"
#include "kernel_shell_cmds.h"
#include "kernel/keyboard.h"

static const char *ksh_help_output
    = { "List of all available commands\n"
        "* help -- Display this message\n"
        "* info -- Display information about the kernel\n"
        "* clear -- Clear screen\n"
        "* echo [string] -- Output string to the screen\n"
        "* loadkeys [string] -- Load a specific keymap\n"
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
ksh_loadkeys (const char * args)
{
  for (int i=0; i < MAX_LAYOUT_ENTRY; i++)
  {
    size_t map_str_len = __kstrlen(layout_map_table[i].map_name);
    if (__kstrneq(args, layout_map_table[i].map_name, map_str_len))
    {
      keyboard_change_layout(layout_map_table[i].mapping_value);
      __kputs("Success\n");
      return;
    }
  }

  __kputs("Unknown keymap\n");
}

void
ksh_listkeys (const char* args)
{
  // so here we will need to iterate over it
  __kputs("List of keymaps:\n");
  for (int i=0; i < MAX_LAYOUT_ENTRY; i++)
  {
    __kputs(layout_map_table[i].map_name);
    __kputc('\n');
  }
}