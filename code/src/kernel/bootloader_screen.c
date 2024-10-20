#include "shell.h"

#define LOGO \
"        :::      ::::::::"\
"      :+:      :+:    :+:"\
"    +:+ +:+         +:+  "\
"  +#+  +:+       +#+     "\
"+#+#+#+#+#+   +#+        "\
"     #+#    #+#          "\
"    ###   ########.fr    "
           

int wait_user_input(char c)
{
    return 1;
}

void bootloader_screen(void)
{
	VGA_DISABLE_CURSOR

	t_terminal terminal = {
		.default_color = {
			.fg = VGA_COLOR_RED,
			.bg = VGA_COLOR_BLACK,
		}
	};

	terminal_clear(&terminal);

	for (size_t y = 0; y < 7; y++) {
		for (size_t x = 0; x < 25; x++) {
			const size_t index = y * 25 + x;
			terminal_putchar_at(
				&terminal, 
				(t_vec2){
					.x = x + (VGA_WIDTH - 25) / 2,
					.y = y + (VGA_HEIGHT - 7) / 2,
				},
				LOGO[index]
			);
		}
	}
	vga_main_frame_update(terminal.vga_frame);
	
	while (keyboard_handler(wait_user_input) == 0);
}