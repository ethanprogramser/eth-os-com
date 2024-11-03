#include "kernel/vga.h"
#include "kernel/util.h"
#include "klib/kmemory.h"

#define __K_DEFAULT_VGA_WIDTH 80
#define __K_DEFAULT_VGA_HEIGHT 25

#define __K_VGA_BASE 0x0B8000

#define __K_VGA_DEFAULT_COLOR (VGA_COLOR_BLUE << 12) | (VGA_COLOR_WHITE << 8)

struct VgaState
{
  uint16_t color;
  uint32_t width, height;

  uint32_t line, column;

  uint16_t *base;
};

static struct VgaState vga_state = { 0 };

void
__vga_new_line (void)
{
  if (vga_state.line < vga_state.height - 1)
    vga_state.line++;
  else
    vga_scroll (1);

  vga_state.column = 0;
  vga_move_cursor (vga_state.column, vga_state.line);
}

uint16_t
vga_color (enum VgaColor bg_color, enum VgaColor fg_color)
{
  return (bg_color << 12) | (fg_color << 8);
}

void
vga_init (void)
{
  vga_state.base = (uint16_t *)__K_VGA_BASE;
  vga_reset ();
}

void
vga_set_color (enum VgaColor bg_color, enum VgaColor fg_color)
{
  vga_state.color = vga_color (bg_color, fg_color);
}

void
vga_clear_color (void)
{
  for (uint8_t *vga_mem = (uint8_t *)vga_state.base;
       vga_mem < (uint8_t *)(vga_state.base
                             + (vga_state.width * vga_state.height * 2));
       vga_mem += 2)
    *(vga_mem + 1) = (uint8_t)(vga_state.color >> 8);
}

void
vga_clear_screen (void)
{
  __kmemset (vga_state.base, 0, vga_state.width * vga_state.height * 2);
  vga_clear_color ();
  vga_state.column = 0;
  vga_state.line = 0;
}

void
vga_print (char c)
{
  switch (c)
  {
  case '\n':
  {
    __vga_new_line ();
  }
  break;

  case '\r':
  {
    vga_state.column = 0;
    vga_move_cursor (vga_state.column, vga_state.line);
  }
  break;

  case '\b':
  {
    if (vga_state.column == 0 && vga_state.line != 0)
    {
      vga_state.line--;
      vga_state.column = vga_state.width;
    }
    vga_state.base[vga_state.line * vga_state.width + (--vga_state.column)]
        = ' ' | vga_state.color;
    vga_move_cursor (vga_state.column, vga_state.line);
  }
  break;

  case '\t':
  {
    if (vga_state.column == vga_state.width)
      __vga_new_line ();
    uint8_t tab_len = 8 - (vga_state.column % 8);
    for (; tab_len > 0; tab_len--)
    {
      vga_state.base[vga_state.line * vga_state.width + vga_state.column]
          = ' ' | vga_state.color;
      vga_state.column++;
    }
    vga_move_cursor (vga_state.column, vga_state.line);
  }
  break;

  default:
  {
    if (vga_state.column == vga_state.width)
      __vga_new_line ();

    vga_state.base[vga_state.line * vga_state.width + vga_state.column]
        = c | vga_state.color;
    vga_state.column++;
    vga_move_cursor (vga_state.column, vga_state.line);
  }
  break;
  }
}

void
vga_scroll (uint32_t lines)
{
  for (uint32_t l = 0; l < lines; l++)
  {
    for (uint16_t y = 0; y < vga_state.height; y++)
      for (uint16_t x = 0; x < vga_state.width; x++)
        vga_state.base[(y - 1) * vga_state.width + x]
            = vga_state.base[y * vga_state.width + x];

    for (uint16_t x = 0; x < vga_state.width; x++)
      vga_state.base[(vga_state.height - 1) * vga_state.width + x]
          = ' ' | vga_state.color;
  }
}

void
vga_reset (void)
{
  vga_state.base = (uint16_t *)__K_VGA_BASE;

  vga_state.column = 0;
  vga_state.line = 0;

  vga_state.width = __K_DEFAULT_VGA_WIDTH;
  vga_state.height = __K_DEFAULT_VGA_HEIGHT;

  vga_set_color (VGA_COLOR_BLACK, VGA_COLOR_WHITE);
  vga_clear_screen ();

  vga_disable_cursor ();
}

void
vga_enable_cursor (void)
{
  outPortB (0x3D4, 0x0A);
  outPortB (0x3D5, (inPortB (0x3D5) & 0xC0));

  outPortB (0x3D4, 0x0B);
  outPortB (0x3D5, (inPortB (0x3D5) & 0xE0) | (vga_state.width << 8)
                       | vga_state.height);
}

void
vga_disable_cursor (void)
{
  outPortB (0x3D4, 0x0A);
  outPortB (0x3D5, 0x20);
}

void
vga_move_cursor (uint8_t x, uint8_t y)
{
  uint16_t pos = y * vga_state.width + x;
  vga_state.column = x;
  vga_state.line = y;

  outPortB (0x3D4, 0x0F);
  outPortB (0x3D5, (uint8_t)(pos & 0xFF));
  outPortB (0x3D4, 0x0E);
  outPortB (0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}
