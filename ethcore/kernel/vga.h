#ifndef __K_VGA_H__
#define __K_VGA_H__

#include "klib/kint.h"

#define VGA_COLOR(b, f) ((uint16_t)(((b) << 12) | ((f) << 8)))

enum VgaColor
{
  VGA_COLOR_BLACK = 0x00,
  VGA_COLOR_BLUE = 0x01,
  VGA_COLOR_GREEN = 0x02,
  VGA_COLOR_CYAN = 0x03,
  VGA_COLOR_RED = 0x04,
  VGA_COLOR_MAGENTA = 0x05,
  VGA_COLOR_BROWN = 0x06,
  VGA_COLOR_LGREY = 0x07,
  VGA_COLOR_DGREY = 0x08,
  VGA_COLOR_LBLUE = 0x09,
  VGA_COLOR_LGREEN = 0x0A,
  VGA_COLOR_LCYAN = 0x0B,
  VGA_COLOR_LRED = 0x0C,
  VGA_COLOR_LMAGENTA = 0x0D,
  VGA_COLOR_LBROWN = 0x0E,
  VGA_COLOR_WHITE = 0x0F,
};

void vga_init (void);
void vga_set_color (uint16_t color);
void vga_clear_color (void);
void vga_clear_screen (void);
void vga_print (char c);
void vga_scroll (uint32_t lines);
void vga_reset (void);
void vga_enable_cursor (void);
void vga_disable_cursor (void);
void vga_move_cursor (uint8_t x, uint8_t y);

#endif // __K_VGA_H__
