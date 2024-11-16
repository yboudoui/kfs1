module kernel;

import shell;
import vga;
import keyboard::scancode;
import context;

struct Multiplexer
{
    Shell[2] shells;

    Shell* current;
}

fn void Multiplexer.init(Multiplexer* this)
{
    this.shells[0].init(Color.WHITE);
	this.shells[1].init(Color.LIGHT_MAGENTA);
    this.current = &this.shells[0];
	vga::enable_cursor(14,15);
}

fn int Multiplexer.handle_input(Multiplexer* this, Scancode key_scancode)
{
    if (key_scancode == Scancode.KEY_1 || key_scancode == Scancode.KEY_2)
    {
        this.current = &this.shells[key_scancode - Scancode.KEY_1];
    }
    return this.current.handle_input(key_scancode);
}

fn void Multiplexer.update(Multiplexer* this)
{
    this.current.update();
}