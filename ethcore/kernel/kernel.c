#include "kernel/gdt.h"
#include "kernel/idt.h"
#include "kernel/keyboard.h"
#include "kernel/timer.h"
#include "kernel/util.h"
#include "kernel/vga.h"
#include "klib/kint.h"
#include "klib/kio.h"

void set_screen_color(uint8_t color);

void set_screen_color(uint8_t color) {
  uint8_t *video_memory = (uint8_t *)0xB8000;

  for (int i = 0; i < width * height * 2; i += 2) {
    video_memory[i + 1] = color; // Set the background color byte
  }
}

void main(void) {
  initGdt();
  initIdt();
  initTimer();
  initKeyboard();
  print("######################\n");
  print("#        ETHOS       #\n");
  print("######################\n");
  print("ethos-->");
  set_screen_color(0x1F);
  for (;;)
    ;
}
