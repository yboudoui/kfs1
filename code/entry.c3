module kernel;

import shell;
import vga;
import std_io;
import keyboard::scancode;
import utils::string;

struct Multiplexer
{
    Shell[2] shells;

    Shell* current;
}

fn void Multiplexer.init(Multiplexer* this)
{
    this.shells[0].init(Color.WHITE);
	this.shells[1].init(Color.BLACK, Color.LIGHT_MAGENTA);
    this.set_current_shell(0);
	vga::enable_cursor();
}

fn void Multiplexer.set_current_shell(Multiplexer* this, uint shell_nb)
{
    this.current = &this.shells[shell_nb];
    std_io::current_std_io(&this.current.terminal.stdio);
}


fn int Multiplexer.handle_input(Multiplexer* this, Scancode key_scancode)
{
    if (key_scancode == Scancode.KEY_1 || key_scancode == Scancode.KEY_2)
    {
        this.set_current_shell(key_scancode - Scancode.KEY_1);
    }
    return this.current.handle_input(key_scancode);
}

fn void Multiplexer.update(Multiplexer* this)
{
    this.current.update();
}

fn void entry()
{
    Multiplexer mtp;

    bool stop = false;

    mtp.init();

	while(stop == false)
	{
		if (keyboard::handler(<Multiplexer>)(&mtp)) stop = true;
        mtp.update();
	}
}