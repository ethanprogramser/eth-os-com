#include "kernel/gdt.h"
#include "kernel/idt.h"
#include "kernel/keyboard.h"
#include "kernel/timer.h"
#include "kernel/vga.h"
#include "klib/kint.h"
#include "klib/kio.h"

void
main (void)
{
  initGdt ();
  initIdt ();
  initTimer ();
  initKeyboard ();
  vga_init ();
  __kputs ("######################\n");
  __kputs ("#        ETHOS       #\n");
  __kputs ("######################\n");
  vga_set_color (VGA_COLOR_BLUE, VGA_COLOR_WHITE);

  __kputs ("ethos-->");
  vga_enable_cursor ();
  vga_clear_screen ();
  for (;;)
    ;
}
