#include "utils.h"
#include "shell.h"

int terminal_input_fallback(t_terminal* terminal)
{
    terminal->vga_frame.cursor.x += 1;
    return 0;
}

int terminal_input_on_return(t_terminal* terminal)
{
    terminal->vga_frame.cursor.x = 0;
    terminal->vga_frame.cursor.y += 1;
    return 0;
}

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
            .default_handler = terminal_input_fallback,
            .handlers = {
                ['\n'] = terminal_input_on_return,
            }
        },
    };
	current_shell(&shell);
	terminal_clear();
	terminal_update();

	while (keyboard_handler(shell_get_character) == 0);
}