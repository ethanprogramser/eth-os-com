#include "kernel/keycodes.h"

static enum Keycode qwerty_keycodes[0xFF] = {
  0,

  KEYCODE_ESCAPE,

  KEYCODE_1,
  KEYCODE_2,
  KEYCODE_3,
  KEYCODE_4,
  KEYCODE_5,
  KEYCODE_6,
  KEYCODE_7,
  KEYCODE_8,
  KEYCODE_9,
  KEYCODE_0,

  KEYCODE_MINUS,
  KEYCODE_EQUAL,
  KEYCODE_TAB,

  KEYCODE_Q,
  KEYCODE_W,
  KEYCODE_E,
  KEYCODE_R,
  KEYCODE_T,
  KEYCODE_Y,
  KEYCODE_U,
  KEYCODE_I,
  KEYCODE_O,
  KEYCODE_P,
  KEYCODE_BRACO,
  KEYCODE_BRACC,
  KEYCODE_RETURN,

  0,

  KEYCODE_A,
  KEYCODE_S,
  KEYCODE_D,
  KEYCODE_F,
  KEYCODE_G,
  KEYCODE_H,
  KEYCODE_J,
  KEYCODE_K,
  KEYCODE_L,
  KEYCODE_SEMICOL,
  KEYCODE_QUOT,

  KEYCODE_TILDE,

  0,

  KEYCODE_BSLASH,

  KEYCODE_Z,
  KEYCODE_X,
  KEYCODE_C,
  KEYCODE_V,
  KEYCODE_B,
  KEYCODE_N,
  KEYCODE_M,
  KEYCODE_COMMA,
  KEYCODE_PERIOD,
  KEYCODE_SLASH,

  0,
  0,
  0,

  KEYCODE_SPACE,
  KEYCODE_CAPS,

  KEYCODE_F1,
  KEYCODE_F2,
  KEYCODE_F3,
  KEYCODE_F4,
  KEYCODE_F5,
  KEYCODE_F6,
  KEYCODE_F7,
  KEYCODE_F8,
  KEYCODE_F9,
  KEYCODE_F10,

  0,

  KEYCODE_LOCK,

  KEYCODE_HOME,
  KEYCODE_UP,
  KEYCODE_PRIOR,
  0,
  KEYCODE_LEFT,
  0,
  KEYCODE_RIGHT,
  0,
  KEYCODE_END,
  KEYCODE_DOWN,
  KEYCODE_NEXT,
  KEYCODE_INSERT,
  KEYCODE_DELETE,
  0,
  0,
  0,

  KEYCODE_F11,
  KEYCODE_F12,

  0,
  0,

  0,
  0,

  KEYCODE_MENU,

  0,
  0,
};

static enum Keycode
scancode_to_keycode (enum Scancode scancode, enum LayoutMapping layout)
{
  // TODO: make use of `layout`.
  return qwerty_keycodes[scancode & 0xFF];
}

static enum KeyModifier
scancode_to_keymodifier (enum Scancode scancode)
{
  switch (scancode)
  {
  case SCANCODE_LSHIFT:
    return KEYMOD_LSHIFT;
  case SCANCODE_LCONTROL:
    return KEYMOD_LCONTROL;
  case SCANCODE_LALT:
    return KEYMOD_LALT;
  case SCANCODE_LWIN:
    return KEYMOD_LSUPER;
  default:
    return 0;
  }
}
