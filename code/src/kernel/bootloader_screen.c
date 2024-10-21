#include "shell.h"

#define LOGO \
"        :::      ::::::::"\
"      :+:      :+:    :+:"\
"    +:+ +:+         +:+  "\
"  +#+  +:+       +#+     "\
"+#+#+#+#+#+   +#+        "\
"     #+#    #+#          "\
"    ###   ########.fr    "

int	wait_user_input(t_key_scancode key_scancode)
{
    return 1;
}

void bootloader_screen(void)
{
	VGA_DISABLE_CURSOR
	static t_terminal terminal = {
		.default_handler = wait_user_input,
		.default_color = {
			.fg = VGA_COLOR_RED,
			.bg = VGA_COLOR_BLACK,
		}
	};
	terminal_current(&terminal);
	terminal_clear();
	
	for (size_t y = 0; y < 7; y++) {
		for (size_t x = 0; x < 25; x++) {
			const size_t index = y * 25 + x;
			terminal_putchar_at(
				(t_vec2){
					.x = x + (VGA_WIDTH - 25) / 2,
					.y = y + (VGA_HEIGHT - 7) / 2,
				},
				LOGO[index]
			);
		}
	}
	terminal_update();
	while (keyboard_handler(terminal_handle_input) == 0);
}
