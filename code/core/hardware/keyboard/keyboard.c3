module keyboard;

import keyboard::scancode;
import hardware;

// Basic IO
fn Scancode geKey_scancode()
{
    const uint KEYBOARD_DATA_PORT = 0x60;
    return (Scancode)hardware::inb(KEYBOARD_DATA_PORT);
}

enum Key_state
{
  KEY_RELEASED,
  KEY_PRESSED,
}

const Key_state[(int)scancode::Scancode.MAX_KEY_SCANCODE] KEYBOARD_STATE = {  }; // KEY_RELEASED

fn Scancode set_keyboard_state(Scancode scancode)
{
    int s = (int)scancode;
    if (s & 0x80)
    {
        s ^= 0x80;
        KEYBOARD_STATE[s] = KEY_RELEASED;
    }
    else {
        KEYBOARD_STATE[s] = KEY_PRESSED;
    }
    return (Scancode)s;
}

fn Scancode get_key_on_pressed()
{
    static Scancode last_scancode;
    int             scancode;
    
    scancode = (int)geKey_scancode();
    if (scancode == 0xE0) {
        scancode = (int)set_keyboard_state(geKey_scancode());
    } else {
        scancode = (int)set_keyboard_state((Scancode)scancode);
    }

    if (KEYBOARD_STATE[scancode] == KEY_RELEASED) {
        last_scancode = (Scancode)0;
        return (Scancode)0;
    }
    if (last_scancode == (Scancode)scancode) return (Scancode)0;
    last_scancode = (Scancode)scancode;
    return (Scancode)scancode;
}