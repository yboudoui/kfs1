#include "keyboard.h"

t_fp_input_handler current_keyboard_handler(t_fp_input_handler handler)
{
    static t_fp_input_handler current_input_handler = NULL;
    if (handler != NULL) {
        current_input_handler = handler;
    }
    return current_input_handler;
}


// t_keyboard_handlers* current_keyboard_handlers(t_keyboard_handlers* handlers)
// {
//     static t_keyboard_handlers* current_input_handlers = NULL;
//     if (handlers != NULL) {
//         current_input_handlers = handlers;
//     }
//     return current_input_handlers;
// }

// int keyboard_handle_input(t_key_scancode key_scancode)
// {
//     CURRENT_KEYBOARD_HANDLERS
//     t_fp_input_handler handler;

//     handler = keyboard_handlers->handlers[key_scancode];
//     if (handler == NULL)
//         handler = keyboard_handlers->default_handler;
//     return handler(key_scancode);
// }

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

int keyboard_handler(void)
{
    KEYBOARD_HANDLER
    t_key_scancode  scancode;
    int             handler_output;

    scancode = get_key_on_pressed();
    if (scancode) {
        if (input_handler == NULL) {
            printf("%p", input_handler);
        }
        handler_output = input_handler(scancode);
        if (handler_output) {
            return handler_output;
        }

    }
    
    return 0;
}