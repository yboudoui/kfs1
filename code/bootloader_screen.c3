module kernel;

import terminal;
import keyboard::scancode;
import keyboard;
import vga;

struct BootLoader
{
	Terminal terminal;
}

fn void BootLoader.init(BootLoader* this) 
{
	vga::disable_cursor();
	this.terminal.init(Color.RED);
}

fn int BootLoader.handle_input(BootLoader* this, Scancode s) 
{
	return 42;
}

fn void BootLoader.update(BootLoader *this) 
{
	put_logo(&this.terminal);
	this.terminal.update();
}

fn void bootloader()
{
    BootLoader bt;

    bool stop = false;

    bt.init();
	while(stop == false)
	{
		if (keyboard::handler(<BootLoader>)(&bt)) stop = true;
        bt.update();
	}
}