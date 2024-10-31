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

#include "ui_box.h"

void show(void)
{
	// print_ui_box((t_ui_box){
	// 	.outer_size = {80, 24},
	// 	.position = {0 , 0},
	// });
	terminal_put_block_at(sizeof(LOGO), LOGO, (t_vec2){
		.x = (VGA_WIDTH - 25) / 2,
		.y = (VGA_HEIGHT - 7) / 2,
	});
}

void bootloader_screen(void)
{
	VGA_DISABLE_CURSOR

	t_terminal terminal;
	current_terminal(&terminal);
	terminal_init(
		(t_vga_entry_color){VGA_COLOR_RED, VGA_COLOR_BLACK},
		wait_user_input
	);

	keyboard_handler();
}
