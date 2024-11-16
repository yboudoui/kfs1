module kernel;

import terminal;
import keyboard::scancode;
import keyboard;
import vga;

struct BootLoader
{
	Terminal terminal;
}

fn void BootLoader.init(BootLoader* this) @dynamic
{
	vga::disable_cursor();
	this.terminal.init(Color.RED);
}

fn int BootLoader.handle_input(BootLoader* this, Scancode s) @dynamic
{
	return 42;
}

fn void BootLoader.update(BootLoader *this) @dynamic
{
	put_logo(&this.terminal);
	this.terminal.update();
}