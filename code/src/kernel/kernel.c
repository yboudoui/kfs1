#include "shell.h"

static t_shell shells[2] = {0};

int shell_get_character(t_key_scancode key_scancode)
{
    if (key_scancode == KEY_1 || key_scancode == KEY_2) {
        current_shell(&shells[key_scancode - KEY_1]);
		current_keyboard_handler(shell_get_character);
    }

	current_keyboard_handlers(&shell_scroll); keyboard_handle_input(key_scancode);
	
	CURRENT_SHELL
	shell->terminal.input_handler(key_scancode);
	readline();
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

	current_keyboard_handler(shell_get_character);
	bool stop = false;
	
	while(stop == false)
	{
		if (keyboard_handler()) stop = true;
		terminal_update();
	}
}