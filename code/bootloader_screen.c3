module kernel;

import terminal;
import keyboard::scancode;
import keyboard;
import vga;
import utils::vector;
import utils::string;
import utils::printf;

const char* LOGO = `
        :::      ::::::::
      :+:      :+:    :+:
    +:+ +:+         +:+  
  +#+  +:+       +#+     
+#+#+#+#+#+   +#+        
     #+#    #+#          
    ###   ########.fr    `;

fn int	wait_user_input(Scancode key_scancode)
{
	return 42;
}

fn void show(Terminal* terminal)
{
	terminal.put_block_at(
		string::strlen(LOGO),
		LOGO,
		Vec2{
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

	while(42)
	{

		if (1)
		{

				if (keyboard::handler(terminal.input_handler)) {
					break;
				}


		} else {

			
				if (keyboard::get_key_scancode() & 0x80) {
					terminal.default_color.background = Color.GREEN;
				} else {
					terminal.default_color.background = Color.RED;
				}

		}
		show(&terminal);
		terminal.update();
	}

	vga::enable_cursor(14,15);
	while(1) {

	terminal.default_color.background = Color.CYAN;
	terminal.clear();
	terminal.update();
	}

}
