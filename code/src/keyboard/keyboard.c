#include "keyboard.h"
#include <stddef.h>

typedef int (*t_fp_input_handler)(t_key_scancode);
typedef struct s_input_handler {
  t_fp_input_handler default_handler;
  t_fp_input_handler handlers[MAX_KEY_SCANCODE];
} t_input_handler;

t_input_handler* current_input_handler(t_input_handler* handler)
{
    static t_input_handler* current_input_handler = NULL;
    if (handler != NULL) {
        current_input_handler = handler;
    }
    return current_input_handler;
}

int handle_input(t_key_scancode key_scancode)
{
    t_input_handler* input_handler = current_input_handler(NULL);
    t_fp_input_handler handler;

    handler = input_handler->handlers[key_scancode];
    if (handler == NULL)
        handler = input_handler->default_handler;
    return handler(key_scancode);
}

t_key_scancode get_key_on_pressed(void)
{
    t_key_scancode scancode = get_key_scancode();

    if (scancode & 0x80) {
        scancode ^= 0x80;
        keyboard_state[scancode] = KEY_RELEASED;
    } else if (keyboard_state[scancode] == KEY_RELEASED) {
        keyboard_state[scancode] = KEY_PRESSED;
        return scancode;
    }
    return 0;
}

int keyboard_handler(t_fp_get_key_scancode handler)
{
    t_key_scancode  scancode;
    int             handler_output;
    
    while (1)
    {
        scancode = get_key_on_pressed();
        if (scancode) {
            handler_output = handler(scancode);
            if (handler_output)
                return handler_output;
        }
    }
    return 0;
}