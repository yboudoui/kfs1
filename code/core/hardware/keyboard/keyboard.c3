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

State[Scancode.elements] keyboard_state = {[0..Scancode.elements] = State.RELEASED};
import utils;


// TODO: better management of the state cf 1
bool extend = false;
fn bool get_key_state(Key_State* key)
{
    *key = Key_State{};
    Hl scancode;

    scancode.raw = hardware::inb(KEYBOARD_DATA_PORT);

    // If the received code is out of the SCANCODE_SET len we abort
    if (!(scancode.code > 0 && scancode.code < scancode::SCANCODE_SET.len)) return false;

    // TODO: cf 1
    if (scancode.extend == 0xE0 && extend == false) {
        extend = true;
    }

    if (extend) {
        *key = scancode::SCANCODE_SET_EXTENDED[scancode.code];
        if (key.state == State.RELEASED) extend = false;
    } else {
        *key = scancode::SCANCODE_SET[scancode.code];
    }


    // If the scancode is not in the table we abort
    if (key.code == Scancode.NONE) return false;
    if (keyboard_state[key.code] == key.state) return false;

    keyboard_state[key.code] = key.state;
    return true;
}