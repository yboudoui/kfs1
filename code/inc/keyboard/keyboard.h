#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "hardware_io.h"
#include "keyboard_scancode.h"
#include "codepage_437.h"
#include <stddef.h>

#define KEYBOARD_DATA_PORT 0x60

static inline t_key_scancode get_key_scancode(void)
{
  return inb(KEYBOARD_DATA_PORT);
} 

typedef enum {
  KEY_RELEASED,
  KEY_PRESSED,
} t_key_state;

typedef int (*t_fp_input_handler)(t_key_scancode);

t_fp_input_handler current_keyboard_handler(t_fp_input_handler handler);
#define KEYBOARD_HANDLER t_fp_input_handler input_handler = current_keyboard_handler(NULL);


typedef struct s_keyboard_input_handler {
  t_fp_input_handler default_handler;
  t_fp_input_handler handlers[MAX_KEY_SCANCODE];
} t_keyboard_handlers;

// t_keyboard_handlers* current_keyboard_handlers(t_keyboard_handlers* handlers);
// #define CURRENT_KEYBOARD_HANDLERS t_keyboard_handlers* keyboard_handlers = current_keyboard_handlers(NULL);

static t_key_state keyboard_state[MAX_KEY_SCANCODE] = {KEY_RELEASED};

// int keyboard_handle_input(t_key_scancode key_scancode);
int keyboard_handler(void);


#endif