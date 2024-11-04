#include "kernel/kernel_shell_cmds.h"
#include "kernel/info.h"
#include "kernel/vga.h"
#include "klib/kio.h"
#include "klib/kstring.h"

static const char *ksh_help_output
    = { "List of all available commands\n"
        "* help -- Display this message\n"
        "* info -- Display information about the kernel\n"
        "* clear -- Clear screen\n"
        "* echo [string] -- Output string to the screen\n"
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
