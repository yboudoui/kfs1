#include "terminal.h"
#include "keyboard.h"

#define LOGO \
"        :::      ::::::::\n"\
"      :+:      :+:    :+:\n"\
"    +:+ +:+         +:+  \n"\
"  +#+  +:+       +#+     \n"\
"+#+#+#+#+#+   +#+        \n"\
"     #+#    #+#          \n"\
"    ###   ########.fr    \n"

int	wait_user_input(t_key_scancode key_scancode)
{
    return 1;
}

void bootloader_screen(void)
{
	VGA_DISABLE_CURSOR
	static t_terminal terminal = {
		.input_handler = wait_user_input,
		.default_color = {
			.fg = VGA_COLOR_RED,
			.bg = VGA_COLOR_BLACK,
		}
	};
	terminal_current(&terminal);
	terminal_clear();
	
	terminal_put_block_at(LOGO, (t_vec2){
		.x = (VGA_WIDTH - 25) / 2,
		.y = (VGA_HEIGHT - 7) / 2,
	});

	terminal_update();
	while (keyboard_handler(terminal_handle_input) == 0);
}
