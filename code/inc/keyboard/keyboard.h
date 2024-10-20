#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "io.h"
#include "keyboard_mapping.h"
#include "codepage_437.h"
#define KEYBOARD_DATA_PORT 0x60

typedef enum {
  KEY_RELEASED,
  KEY_PRESSED,
} t_key_state;

typedef int (*t_fp_get_character)(char c);
static t_key_state keyboard_state[MAX_KEYBOARD] = {KEY_RELEASED};

int           keyboard_handler(t_fp_get_character handler);

#endif