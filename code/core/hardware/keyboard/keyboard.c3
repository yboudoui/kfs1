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

// Key_State a;
// Key_State b;

// TODO: better management of the state cf 1
bool extend = false;
fn bool get_key_state(Key_State* key)
{
    *key = Key_State{};
    Hl scancode;

    scancode.raw = hardware::inb(KEYBOARD_DATA_PORT);

    // If the received code is out of the SCANCODE_SET len we abort
    if (!(scancode.code > 0 && scancode.code < scancode::SCANCODE_SET.len)) return false;

    // a.code = Scancode.NONE;
    // b.code = Scancode.NONE;


    // TODO: cf 1
    if (scancode.extend == 0xE0 && extend == false) {
        extend = true;
    }

    if (extend) {
        *key = scancode::SCANCODE_SET_EXTENDED[scancode.code];
        // a = *key;
        if (key.state == State.RELEASED) extend = false;
    } else {
        *key = scancode::SCANCODE_SET[scancode.code];
        // b = *key;
    }


    // If the scancode is not in the table we abort
    if (key.code == Scancode.NONE) return false;
    if (keyboard_state[key.code] == key.state) return false;

    // utils::string::printf("{ %x }",  scancode.raw);
    // utils::string::printf("\n\n%x { [%s] %s }", scancode.raw,  Scancode.names[a.code], State.names[a.state]);
    // utils::string::printf("\n%x { [%s] %s }", scancode.raw, Scancode.names[b.code], State.names[b.state]);

    keyboard_state[key.code] = key.state;
    return true;
}