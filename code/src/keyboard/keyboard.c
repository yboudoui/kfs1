#include "keyboard.h"


unsigned char get_scancode(void)
{
    return inb(KEYBOARD_DATA_PORT);
}

unsigned char update_keyboard_state(unsigned char scancode)
{
    if (scancode & 0x80) {
        scancode ^= 0x80;
        keyboard_state[scancode] = KEY_RELEASED;
    }
    else {
        keyboard_state[scancode] = KEY_PRESSED;
    }
    return scancode;
}

char keyboard_handler(void)
{
    unsigned char scancode;

    scancode = get_scancode();

    t_key_state old = keyboard_state[scancode];

    scancode = update_keyboard_state(scancode);

    if (old == KEY_RELEASED && keyboard_state[scancode] == KEY_PRESSED) {
        return codepage_437[scancode];
    }
    return 0;
}