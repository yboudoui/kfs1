module keyboard;

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