module keyboard(<Type>);

def Fp_input_handler = fn int (Type*, Scancode);

struct Keyboard_handlers
{
    Type*                                               ref;
    Fp_input_handler                                    default_handler;
    Fp_input_handler[(int)Scancode.MAX_KEY_SCANCODE]    handlers;
}

fn int Keyboard_handlers.handle_input(Keyboard_handlers* this, Scancode key_scancode) 
{
    Fp_input_handler handler;

    handler = this.handlers[key_scancode];
    if (handler == null) handler = this.default_handler;
    if (handler == null) return 0;
    return handler(this.ref, key_scancode); 
}

fn int handler(Type* ref)
{
    int             output;
    Scancode        scancode = keyboard::io::get_key_on_pressed();

    if (scancode != Scancode.NONE) output = ref.handle_input(scancode);
    return output;
}