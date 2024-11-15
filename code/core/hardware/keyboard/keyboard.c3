module keyboard;

import keyboard::scancode;
import hardware;
import utils::memory;

const ushort KEYBOARD_DATA_PORT = 0x60;
fn char get_key_scancode()
{
    return (char)hardware::inb(KEYBOARD_DATA_PORT);
} 


bool[217] keyboard_state;

fn char set_keyboard_state(char scancode)
{
    if (scancode & 0x80)
    {
        scancode ^= 0x80;
        keyboard_state[scancode] = false;
    }
    else {
        keyboard_state[scancode] = true;
    }
    return scancode;
}

fn Scancode get_key_on_pressed()
{
    static Scancode last_scancode;
    char             scancode;
    
    scancode = get_key_scancode();
    if (scancode == 0xE0) {
        scancode = set_keyboard_state(get_key_scancode());
    } else {
        scancode = set_keyboard_state(scancode);
    }
    if (keyboard_state[scancode] == false) {
        last_scancode = Scancode.NONE;
        return Scancode.NONE;
    }
    if (last_scancode == scancode::SCANCODE_SET[scancode]) return Scancode.NONE;
    last_scancode = scancode::SCANCODE_SET[scancode];
    return  scancode::SCANCODE_SET[scancode];
}