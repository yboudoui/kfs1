#ifndef KEYBOARD_MAPPING_H
#define KEYBOARD_MAPPING_H

typedef enum {
  KEY_ESCAPE = 1,
  KEY_1,
  KEY_2,
  KEY_3,
  KEY_4,
  KEY_5,
  KEY_6,
  KEY_7,
  KEY_8,
  KEY_9,
  KEY_0,
  KEY_DASH,
  KEY_EQUAL,
  KEY_BACKSPACE,

  KEY_TAB,
  KEY_Q,
  KEY_W,
  KEY_E,
  KEY_R,
  KEY_T,
  KEY_Y,
  KEY_U,
  KEY_I,
  KEY_O,
  KEY_P,
  KEY_OPEN_SQUARE_BRACKET,
  KEY_CLOSE_SQUARE_BRACKET,

  KEY_ENTER,
  KEY_RIGHT_CONTROL,

  KEY_A,
  KEY_S,
  KEY_D,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_SEMI_COLON,
  KEY_SINGLE_QUOTE,


  LOL,
  KEY_LEFT_SHIFT,

  KEY_LEFT_CONTROL,
  // KEY_BACK_SLASH,
  KEY_Z,
  KEY_X,
  KEY_C,
  KEY_V,
  KEY_B,
  KEY_N,
  KEY_M,
  KEY_COMA,
  KEY_POINT,
  KEY_SLASH,
  KEY_RIGHT_SHIFT,

  KEY_PAD_STAR,
  KEY_LEFT_ALT,
  KEY_SPACE,
  KEY_CAPS_LOCK,

  KEY_F1,
  KEY_F2,
  KEY_F3,
  KEY_F4,
  KEY_F5,
  KEY_F6,
  KEY_F7,
  KEY_F8,
  KEY_F9,
  KEY_F10,

  KEY_NUMBER_LOCK,
  KEY_SCROLL_LOCK,

  KEY_NUMPAD_7,
  KEY_NUMPAD_8,
  KEY_NUMPAD_9,
  KEY_NUMPAD_MINUS,
  KEY_NUMPAD_4,
  KEY_NUMPAD_5,
  KEY_NUMPAD_6,
  KEY_NUMPAD_PLUS,
  KEY_NUMPAD_1,
  KEY_NUMPAD_2,
  KEY_NUMPAD_3,
  KEY_NUMPAD_0,
  KEY_NUMPAD_DOTE,

  EMPTY_0,
  EMPTY_1,

  KEY_F11,
  KEY_F12,

  KEY_LEFT_WINDOWS,
  KEY_RIGHT_ALT,
  KEY_RIGHT_WINDOWS,
  KEY_BACK_SLASH,

  MAX_KEY_SCANCODE,

  // Synonyme of key Scan Code Set 1
  KEY_DELETE    = KEY_NUMPAD_DOTE,
  KEY_LEFT      = KEY_NUMPAD_4,
  KEY_RIGHT     = KEY_NUMPAD_6,
  KEY_UP        = KEY_NUMPAD_8,
  KEY_DOWN      = KEY_NUMPAD_2,

  KEY_HOME      = KEY_NUMPAD_7,
  KEY_END       = KEY_NUMPAD_1,
  KEY_PAGE_UP   = KEY_NUMPAD_9,
  KEY_PAGE_DOWN = KEY_NUMPAD_3,

  KEY_IS_NUMBER = KEY_0 | KEY_1 | KEY_2 | KEY_3 | KEY_4 | KEY_5 | KEY_6 | KEY_7 | KEY_8 | KEY_9,
} t_key_scancode;



#endif