module kernel;

import terminal;
import keyboard::scancode;
import vga;
import utils::vector;
import utils::string;

const char* LOGO = `
        :::      ::::::::\n
      :+:      :+:    :+:\n
    +:+ +:+         +:+  \n
  +#+  +:+       +#+     \n
+#+#+#+#+#+   +#+        \n
     #+#    #+#          \n
    ###   ########.fr    \n`;

fn int	wait_user_input(scancode::Scancode key_scancode)
{
    return 42;
}

// #include "ui_box.h"

fn void show(Terminal* terminal)
{
	terminal.put_block_at(
		string::strlen(LOGO),
		LOGO,
		vector::Vec2{
			(vga::MAX_WIDTH - 25) / 2,
			(vga::MAX_HEIGHT - 7) / 2,
		}
	);
}

fn void bootloader_screen()
{
	vga::disable_cursor();

	Terminal terminal @noinit;
	terminal.init(Entry_color{Color.RED, Color.BLACK}, &wait_user_input);

	// current_terminal(&terminal);

	while(42)
	{
		// if (keyboard_handler()) return;
		show(&terminal);
		terminal.update();
	}
}
