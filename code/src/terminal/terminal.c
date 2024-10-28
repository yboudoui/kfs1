#include "terminal.h"

void terminal_clear(void)
{
	CURRENT_TERMINAL

	vga_fill(
		&terminal->vga_frame, 
		vga_entry(0, terminal->default_color)
	);
}

void terminal_reset_position(void)
{
	CURRENT_TERMINAL
	terminal->current_position = (t_vec2){0};
}

void terminal_update(void)
{
	CURRENT_TERMINAL
	vga_main_frame_update(terminal->vga_frame);
}

int terminal_handle_input(t_key_scancode key_scancode)
{
    CURRENT_TERMINAL
    t_fp_terminal_input_handler handler;

    handler = terminal->input_handler.handlers[key_scancode];
    if (handler == NULL)
        handler = terminal->input_handler.default_handler;
    return handler(key_scancode);
}