#include "shell.h"

static t_shell shells[2];

int shell_get_character(t_key_scancode key_scancode)
{
    if (key_scancode == KEY_1 || key_scancode == KEY_2) {
        current_shell(&shells[key_scancode - KEY_1]);
    } else {
    	keyboard_handle_input(key_scancode);
	}
    terminal_clear();
	shell();
	vga_main_frame_update();
    return 0;
}

void kernel_main(void)
{	
	VGA_ENABLE_CURSOR

	current_shell(&shells[0]);
	shell_init_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

	current_shell(&shells[1]);
	shell_init_color(VGA_COLOR_LIGHT_MAGENTA, VGA_COLOR_BLACK);

	current_shell(&shells[0]);
	keyboard_handler();
}