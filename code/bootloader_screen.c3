module kernel;

import tty;
import keyboard;
import vga;

fn void bootloader()
{
	Tty			tty;
    Key_State	key;

	tty.init();
	tty.default_color.foreground = Color.RED;

	vga::disable_cursor();

	kernel::put_logo(&tty);
	tty.update();
	
	while (key.state != PRESSED) keyboard::io::get_key_state(&key);
}