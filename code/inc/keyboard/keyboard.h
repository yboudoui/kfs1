#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "keyboard_mapping.h"
#include "codepage_437.h"
#define KEYBOARD_DATA_PORT 0x60


typedef enum {
  KEY_RELEASED,
  KEY_PRESSED,
} t_key_state;

static t_key_state keyboard_state[MAX_KEYBOARD] = {KEY_RELEASED};

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