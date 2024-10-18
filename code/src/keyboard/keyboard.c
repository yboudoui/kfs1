#include "keyboard.h"

const char keyboard[3][15] = {
    {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']'},
    {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 0x27 ,0, 'P', 0x5C},
    {'z', 'x', 'c', 'v', 'b', 'n', 'm', 0x2C, 0X2E, 0x2F},    
    };

unsigned char get_scancode(void)
{
    return inb(KEYBOARD_DATA_PORT);
}

char keyboard_handler(void)
{
    unsigned char scancode;

    scancode = get_scancode();
    if (scancode >= 0x10 && scancode <= 0x1C) {
		return keyboard[0][scancode - 0x10];
	}
    if (scancode >= 0x1E && scancode <= 0x2B) {
		return keyboard[1][scancode - 0x1E];
	}
    if (scancode >= 0x2C && scancode <= 0x35) {
		return keyboard[2][scancode - 0x2C];
	}

    return 0;
}