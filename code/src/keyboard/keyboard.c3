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

// High level IO

def Fp_input_handler = fn int (Scancode);

struct Keyboard_handlers
{
  Fp_input_handler                              default_handler;
  Fp_input_handler[(int)scancode::Scancode.MAX_KEY_SCANCODE]  handlers;
}

fn int Keyboard_handlers.handle_input(Keyboard_handlers this, Scancode key_scancode)
{
    Fp_input_handler handler;

    handler = this.handlers[key_scancode];
    if (handler == null) handler = this.default_handler;
    if (handler == null) return 0;
    return handler(key_scancode);
}

fn int keyboard_handler(Keyboard_handlers handler)
{
    int             handler_output;
    Scancode        scancode = get_key_on_pressed();

    if (scancode != (Scancode)0) {
        handler_output = handler.handle_input(scancode);
    }
    return handler_output;
}