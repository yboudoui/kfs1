#include "terminal.h"

static t_keyboard_handlers terminal_keyboard_handlers = {
    // .default_handler = terminal_input_fallback,
    .handlers = {
        [KEY_ENTER]     = terminal_input_on_return,
        // [KEY_BACKSPACE] = terminal_input_on_backspace,
        // [KEY_DELETE]    = terminal_input_on_del,
        // [KEY_LEFT]      = terminal_input_on_button_left,
        // [KEY_RIGHT]     = terminal_input_on_button_right,
    },
};

t_terminal* current_terminal(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		current_terminal = terminal;
        current_vga_frame(&current_terminal->vga_frame);
        if (current_terminal->input_handler == keyboard_handle_input)
            current_keyboard_handlers(&terminal_keyboard_handlers);
	}
	return current_terminal;
}

void terminal_clear(void)
{
	CURRENT_TERMINAL

	vga_fill(vga_entry(0, terminal->default_color));
	terminal->current_position = (t_vec2){0};
}

void terminal_init(t_vga_entry_color default_color, t_fp_input_handler input_handler)
{
	CURRENT_TERMINAL
	terminal->default_color = default_color;
	terminal->input_handler = keyboard_handle_input;
	if (input_handler)
		terminal->input_handler = input_handler;
}