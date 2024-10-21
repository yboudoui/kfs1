#include "keyboard.h"

int keyboard_handler(t_fp_get_key_scancode handler)
{
    t_key_state     state = KEY_RELEASED;
    unsigned char   scancode = inb(KEYBOARD_DATA_PORT);

    if (scancode & 0x80) {
        scancode ^= 0x80;
        keyboard_state[scancode] = KEY_RELEASED;
        return 0;
    } else if (keyboard_state[scancode] == KEY_RELEASED) {
        keyboard_state[scancode] = KEY_PRESSED;
        return handler(scancode);
    }
    return 0;
}