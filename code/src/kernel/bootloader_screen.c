#include "shell.h"


const static char* logo = 
"        :::      ::::::::"
"      :+:      :+:    :+:"
"    +:+ +:+         +:+  "
"  +#+  +:+       +#+     "
"+#+#+#+#+#+   +#+        "
"     #+#    #+#          "
"    ###   ########.fr    ";
           

int wait_user_input(char c)
{
    return 1;
}

void bootloader_screen(void)
{
	t_terminal_frame frame = {
		.default_color = {
			.fg = VGA_COLOR_RED,
			.bg = VGA_COLOR_BLACK,
		}
	};
	current_terminal_frame(&frame);
	terminal_clear();

	for (size_t y = 0; y < 7; y++) {
		for (size_t x = 0; x < 25; x++) {
			const size_t index = y * 25 + x;
			t_vga_entry entry = vga_entry(logo[index], frame.default_color);

			t_terminal_position position = {
				.column = x + 28,
				.row = y + 9,
			};
			terminal_frame_put_entry_at(&frame.frame, entry, position);
		}

	}
	terminal_update_frame();
	readline(wait_user_input);
}