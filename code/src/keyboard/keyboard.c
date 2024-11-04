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


t_key_scancode set_keyboard_state(t_key_scancode scancode)
{
    if (scancode & 0x80)
    {
        scancode ^= 0x80;
        keyboard_state[scancode] = KEY_RELEASED;
    }
    else {
        keyboard_state[scancode] = KEY_PRESSED;
    }
    return scancode;
}

t_key_scancode get_key_on_pressed(void)
{
    static t_key_scancode last_scancode = 0;
    t_key_scancode scancode = set_keyboard_state(get_key_scancode());

    if (keyboard_state[scancode] == KEY_RELEASED) {
        last_scancode = 0;
        return 0;
    }
    if (last_scancode == scancode) return 0;
    last_scancode = scancode;
    return scancode;
}

int keyboard_handler(void)
{
    KEYBOARD_HANDLER
    t_key_scancode  scancode;
    int             handler_output;

    scancode = get_key_on_pressed();
    if (scancode) {
        handler_output = input_handler(scancode);
        if (handler_output) return handler_output;
    }
    
    return 0;
}