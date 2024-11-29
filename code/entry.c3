module kernel;

import keyboard;
import shell;
import vga;
import utils::string;

fn void entry()
{
	vga::enable_cursor();

    Shell[2] shells;
    Shell* current;

    shells[0].tty.init();
	shells[1].tty.init();

    current = &shells[0];

    bool stop = false;

    string::printf("\e[34m\e[46mHello World\n");
    
	while(stop == false)
	{
        if (current.handle_input()) stop = true;
        // if (key_scancode == Scancode.KEY_1 || key_scancode == Scancode.KEY_2)
        // {
        //     this.set_current_shell(key_scancode - Scancode.KEY_1);
        // }
        current.tty.update();
	}
}