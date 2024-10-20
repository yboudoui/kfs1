#include "terminal.h"

t_terminal* terminal_current(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		terminal = current_terminal;
	}
	return current_terminal;
}

void terminal_clear(void)
{
	t_terminal* terminal = terminal_current(NULL);

	vga_fill(
		&terminal->vga_frame,
		vga_entry(' ', terminal->default_color)
	);
}

void terminal_reset_position(void)
{
	t_terminal* terminal = terminal_current(NULL);
	terminal->current_position = (t_vec2){0};
}

void terminal_update(void)
{
	t_terminal*	terminal = terminal_current(NULL);
	vga_main_frame_update(terminal->vga_frame);
}

int terminal_handle_input(char c)
{
    t_terminal* terminal = terminal_current(NULL);
    t_fp_terminal_input_handler handler;

    handler = terminal->handlers[c];
    if (handler == NULL)
        handler = terminal->default_handler;
    return handler(terminal);
}