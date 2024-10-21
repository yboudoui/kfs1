#ifndef CODEPAGE_437_H
#define CODEPAGE_437_H

#include "keyboard_scancode.h"

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

#endif