#include "kernel/kernel_shell_cmds.h"
#include "kernel/vga.h"

void
ksh_clear (char *_)
{
  vga_clear_screen ();
}
