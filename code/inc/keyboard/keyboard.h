#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "keyboard_scancode.h"
#include "codepage_437.h"
#define KEYBOARD_DATA_PORT 0x60

static inline t_key_scancode get_key_scancode(void)
{
  return inb(KEYBOARD_DATA_PORT);
} 

typedef enum {
  KEY_RELEASED,
  KEY_PRESSED,
} t_key_state;


typedef int (*t_fp_get_key_scancode)(t_key_scancode key);
static t_key_state keyboard_state[MAX_KEY_SCANCODE] = {KEY_RELEASED};

int keyboard_handler(t_fp_get_key_scancode handler);

#endif