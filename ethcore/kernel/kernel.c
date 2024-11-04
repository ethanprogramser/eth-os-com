#include "kernel/gdt.h"
#include "kernel/idt.h"
#include "kernel/kernel_shell.h"
#include "kernel/keyboard.h"
#include "kernel/multiboot.h"
#include "kernel/timer.h"
#include "kernel/vga.h"
#include "klib/kio.h"

void
kmain (size_t magic, struct MultibootInfo *boot)
{
  gdt_init ();
  idt_init ();
  timer_init ();
  vga_init ();
  keyboard_init ();

  __kputs ("Loading Eth-OS...\n");

  kernel_shell_init ();
  kernel_shell_loop ();
}
