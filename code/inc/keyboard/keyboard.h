#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#define KEYBOARD_DATA_PORT 0x60

typedef enum {
  // KEY_BACK_QUOTE = 1,
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

  KEY_PAD_START,
  KEY_LEFT_ALT,
  KEY_SPACE,
  KEY_CAPS_LOCK,


  KEY_LEFT_WINDOWS,
  KEY_RIGHT_ALT,
  KEY_RIGHT_WINDOWS,
  KEY_BACK_SLASH,

  MAX_KEYBOARD,
} t_keyboard_mapping;

typedef enum {
  KEY_RELEASED,
  KEY_PRESSED,
} t_key_state;

static t_key_state keyboard_state[MAX_KEYBOARD] = {0};

static const unsigned char codepage_437[255] = {
  // [KEY_BACK_QUOTE]            = 0x60,
  [KEY_0]                     = '0',
  [KEY_1]                     = '1',
  [KEY_2]                     = '2',
  [KEY_3]                     = '3',
  [KEY_4]                     = '4',
  [KEY_5]                     = '5',
  [KEY_6]                     = '6',
  [KEY_7]                     = '7',
  [KEY_8]                     = '8',
  [KEY_9]                     = '9',
  [KEY_DASH]                  = 0x2D,
  [KEY_EQUAL]                 = 0x3D,
  [KEY_BACKSPACE]             = '\b',

  [KEY_TAB]                   = '\t',
  [KEY_Q]                     = 'q',
  [KEY_W]                     = 'w',
  [KEY_E]                     = 'e',
  [KEY_R]                     = 'r',
  [KEY_T]                     = 't',
  [KEY_Y]                     = 'y',
  [KEY_U]                     = 'u',
  [KEY_I]                     = 'i',
  [KEY_O]                     = 'o',
  [KEY_P]                     = 'p',
  [KEY_OPEN_SQUARE_BRACKET]   = '[',
  [KEY_CLOSE_SQUARE_BRACKET]  = ']',

  [KEY_A]                     = 'a',
  [KEY_S]                     = 's',
  [KEY_D]                     = 'd',
  [KEY_F]                     = 'f',
  [KEY_G]                     = 'g',
  [KEY_H]                     = 'h',
  [KEY_J]                     = 'j',
  [KEY_K]                     = 'k',
  [KEY_L]                     = 'l',
  [KEY_SEMI_COLON]            = ';',
  [KEY_SINGLE_QUOTE]          = 0x27,
  [KEY_ENTER]                 = '\n',

  [KEY_BACK_SLASH]            = 0x5C,
  [KEY_Z]                     = 'z',
  [KEY_X]                     = 'x',
  [KEY_C]                     = 'c',
  [KEY_V]                     = 'v',
  [KEY_B]                     = 'b',
  [KEY_N]                     = 'n',
  [KEY_M]                     = 'm',
  [KEY_COMA]                  = 0x2C,
  [KEY_POINT]                 = 0X2E,
  [KEY_SLASH]                 = 0x2F,

  [KEY_SPACE]                 = ' ',
  0,
};

static __inline unsigned char inb (unsigned short int port)
{
  unsigned char _v;
  __asm__ __volatile__ (
    "inb %1, %0"
    :"=a" (_v)
    :"Nd" (port)
    );
  return _v;
}

unsigned char get_scancode(void);
char keyboard_handler(void);

#endif