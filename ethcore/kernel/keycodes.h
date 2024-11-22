#ifndef __K_KEYCODES_H__
#define __K_KEYCODES_H__

#include "kernel/layout_mappings.h"
#include "kernel/scancodes.h"

enum Keycode
{
  KEYCODE_BACKSPACE = 0x01,
  KEYCODE_SPACE = 0x02,
  KEYCODE_TAB = 0x03,
  KEYCODE_CAPS = 0x04,

  KEYCODE_TILDE = 0x05,
  KEYCODE_MINUS = 0x06,
  KEYCODE_EQUAL = 0x07,
  KEYCODE_BSLASH = 0x08,
  KEYCODE_BRACO = 0x09,
  KEYCODE_BRACC = 0x0A,
  KEYCODE_SEMICOL = 0x0B,
  KEYCODE_QUOT = 0x0C,
  KEYCODE_COMMA = 0x0D,
  KEYCODE_PERIOD = 0x0E,
  KEYCODE_SLASH = 0x0F,

  KEYCODE_0 = 0x10,
  KEYCODE_1 = 0x11,
  KEYCODE_2 = 0x12,
  KEYCODE_3 = 0x13,
  KEYCODE_4 = 0x14,
  KEYCODE_5 = 0x15,
  KEYCODE_6 = 0x16,
  KEYCODE_7 = 0x17,
  KEYCODE_8 = 0x18,
  KEYCODE_9 = 0x19,

  KEYCODE_A = 0x20,
  KEYCODE_B = 0x21,
  KEYCODE_C = 0x22,
  KEYCODE_D = 0x23,
  KEYCODE_E = 0x24,
  KEYCODE_F = 0x25,
  KEYCODE_G = 0x26,
  KEYCODE_H = 0x27,
  KEYCODE_I = 0x28,
  KEYCODE_J = 0x29,
  KEYCODE_K = 0x2A,
  KEYCODE_L = 0x2B,
  KEYCODE_M = 0x2C,
  KEYCODE_N = 0x2D,
  KEYCODE_O = 0x2E,
  KEYCODE_P = 0x2F,
  KEYCODE_Q = 0x30,
  KEYCODE_R = 0x31,
  KEYCODE_S = 0x32,
  KEYCODE_T = 0x33,
  KEYCODE_U = 0x34,
  KEYCODE_V = 0x35,
  KEYCODE_W = 0x36,
  KEYCODE_X = 0x37,
  KEYCODE_Y = 0x38,
  KEYCODE_Z = 0x39,

  KEYCODE_MENU = 0x40,
  KEYCODE_RETURN = 0x41,
  KEYCODE_ESCAPE = 0x42,

  KEYCODE_F1 = 0x50,
  KEYCODE_F2 = 0x51,
  KEYCODE_F3 = 0x52,
  KEYCODE_F4 = 0x53,
  KEYCODE_F5 = 0x54,
  KEYCODE_F6 = 0x55,
  KEYCODE_F7 = 0x56,
  KEYCODE_F8 = 0x57,
  KEYCODE_F9 = 0x58,
  KEYCODE_F10 = 0x59,
  KEYCODE_F11 = 0x5A,
  KEYCODE_F12 = 0x5B,

  KEYCODE_LOCK = 0x5C,

  KEYCODE_UP = 0x60,
  KEYCODE_LEFT = 0x61,
  KEYCODE_DOWN = 0x62,
  KEYCODE_RIGHT = 0x63,

  KEYCODE_PRIOR = 0x70,
  KEYCODE_PGUP = 0x70, // Alias for KEYCODE_PRIOR
  KEYCODE_NEXT = 0x71,
  KEYCODE_PGDOWN = 0x71, // Alias for KEYCODE_NEXT

  KEYCODE_INSERT = 0x72,
  KEYCODE_HOME = 0x73,
  KEYCODE_END = 0x74,
  KEYCODE_DELETE = 0x75,

  KEYCODE_LSHIFT = 0x80,
  KEYCODE_RSHIFT = 0x81,
  KEYCODE_LCONTROL = 0x82,
  KEYCODE_RCONTROL = 0x83,
  KEYCODE_LALT = 0x84,
  KEYCODE_RALT = 0x85,
  KEYCODE_LSUPER = 0x86,
  KEYCODE_RSUPER = 0x87,

  KEYCODE_EXCL = 0x90,
  KEYCODE_AT = 0x91,
  KEYCODE_HASH = 0x92,
  KEYCODE_DOLLARSIGN = 0x93,
  KEYCODE_PERCENT = 0x94,
  KEYCODE_ARROW = 0x95,
  KEYCODE_AMPERSAND = 0x96,
  KEYCODE_SFLAKE = 0x97,
  KEYCODE_PARENO = 0x98,
  KEYCODE_PARENC = 0x99,
  KEYCODE_UNDERLINE = 0x9A,
  KEYCODE_PLUS = 0x9B,

  KEYCODE_BRACEO = 0x100,
  KEYCODE_BRACEC = 0x101,
  KEYCODE_PIPE = 0x102,
  KEYCODE_DDOT = 0x103,
  KEYCODE_DQUOT = 0x104,
  KEYCODE_LTHAN = 0x105,
  KEYCODE_GTHAN = 0x106,
  KEYCODE_QMARK = 0x107,

  KEYCODE_MAX_KEYCODES,
};

extern const enum Keycode qwerty_keycodes[0xFF];
extern const enum Keycode azerty_keycodes[0xFF];

#define MAX_LAYOUT_TABLE_ENTRIES (2ul)
extern const struct LayoutMapTableEntry
    layout_map_table[MAX_LAYOUT_TABLE_ENTRIES];

static inline enum Keycode
scancode_to_keycode (enum Scancode scancode, enum LayoutMapping layout)
{
  switch (layout)
  {
  case LAYOUT_MAPPING_QWERTY:
    return qwerty_keycodes[scancode & 0xFF];

  case LAYOUT_MAPPING_AZERTY:
    return azerty_keycodes[scancode & 0xFF];

  default:
    return 0;
  }
}

#endif // __K_KEYCODES_H__
