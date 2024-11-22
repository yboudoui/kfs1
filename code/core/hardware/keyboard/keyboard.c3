module keyboard::io;

import keyboard::scancode;
import hardware;

const ushort KEYBOARD_DATA_PORT = 0x60;
union Hl 
{
    ushort  raw;
    struct
    {
        char extend;
        char code;
    }
}

State[Scancode.elements] keyboard_state;
import utils;

fn bool get_key_state(Key_State* key)
{
    *key = Key_State{};
    Hl scancode;

    scancode.raw = hardware::inb(KEYBOARD_DATA_PORT);

    // If the received code is out of the SCANCODE_SET len we abort
    if (!(scancode.code > 0 && scancode.code < scancode::SCANCODE_SET.len)) return false;

    if (scancode.extend == 0xE0) {
        *key = scancode::SCANCODE_SET_EXTENDED[scancode.code];
    } else {
        *key = scancode::SCANCODE_SET[scancode.code];
    }
    // If the scancode is not in the table we abort
    if (key.code == Scancode.NONE) return false;
    if (keyboard_state[key.code] == key.state) return false;

    utils::string::printf("{ %x }",  scancode.raw);

    keyboard_state[key.code] = key.state;
    return true;
}