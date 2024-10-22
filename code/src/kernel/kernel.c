#include "utils.h"
#include "shell.h"

#include "keyboard_input_handlers.h"

void kernel_main(void)
{
	VGA_ENABLE_CURSOR

	t_shell shell = {
	    .terminal = (t_terminal){
            .default_color = (t_vga_entry_color){
				.fg = VGA_COLOR_WHITE,
				.bg = VGA_COLOR_BLACK,
			},
            .input_handler		= {
			    .default_handler = terminal_input_fallback,
			    .handlers = {
			        [KEY_ENTER]     = terminal_input_on_return,
			        [KEY_BACKSPACE] = terminal_input_on_backspace,
			        // [KEY_TAB]       = terminal_input_on_tab,
			        [KEY_DELETE]    = terminal_input_on_del,
			        [KEY_LEFT]      = terminal_input_on_button_left,
			        [KEY_RIGHT]     = terminal_input_on_button_right,
			        [KEY_UP]        = terminal_input_on_button_up,
			        [KEY_DOWN]      = terminal_input_on_button_down,
			    }
			},
			.readline_buffer	= NEW_READLINE_BUFFER(2048),
        },
    };
	current_shell(&shell);
	terminal_clear();
	terminal_update();
	while (keyboard_handler(shell_get_character) == 0);
}