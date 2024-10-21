#include "utils.h"
#include "shell.h"

#include "keyboard_input_handlers.h"

void kernel_main(void)
{
	VGA_ENABLE_CURSOR
	t_shell shell = {
        .buffer = {' '},
	    .terminal = (t_terminal){
            .default_color = (t_vga_entry_color){
				.fg = VGA_COLOR_WHITE,
				.bg = VGA_COLOR_BLACK,
			},
            .input_handler = terminal_input_handler(),
        },
    };
	current_shell(&shell);
	terminal_clear();
	terminal_update();

	while (keyboard_handler(shell_get_character) == 0);
}