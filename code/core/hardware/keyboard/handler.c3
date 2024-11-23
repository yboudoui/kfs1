module keyboard(<Type>);
import keyboard::scancode;

def Fp_input_handler = fn int (Type*, Scancode);

struct Keyboard_handlers
{
    Type*                               ref;
    Fp_input_handler                    default_handler;
    Fp_input_handler[Scancode.elements] handlers;
}

fn int Keyboard_handlers.handle_input(Keyboard_handlers* this, Scancode key_scancode) 
{
    Fp_input_handler handler;

    handler = this.handlers[key_scancode];
    if (handler == null) handler = this.default_handler;
    if (handler == null) return 0;
    return handler(this.ref, key_scancode); 
}

import keyboard::io;

import utils;
fn int handler(Type* ref)
{
    Key_State key;

    if (keyboard::io::get_key_state(&key)) {
        if (key.state == PRESSED) {
            return ref.handle_input(key.code);
        }
    }
    return 0;
}