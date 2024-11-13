module kernel;

import terminal;
import keyboard::scancode;
import vga::color;

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

// fn void show(void)
// {
// 	terminal_put_block_at(sizeof(LOGO), LOGO, (t_vec2){
// 		.x = (VGA_WIDTH - 25) / 2,
// 		.y = (VGA_HEIGHT - 7) / 2,
// 	});
// }

fn void bootloader_screen()
{
	// VGA_DISABLE_CURSOR

	terminal::Terminal terminal @noinit;

	terminal.init(vga::color::Entry_color{vga::color::Color.RED, vga::color::Color.BLACK}, &wait_user_input);

	// current_terminal(&terminal);

	while(42)
	{
		terminal.clear();
		// if (keyboard_handler()) return;
		// show();
		terminal.update();
	}
}
