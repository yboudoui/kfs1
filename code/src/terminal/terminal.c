#include "terminal.h"

t_terminal* current_terminal(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		current_terminal = terminal;
        current_vga_frame(&current_terminal->vga_frame);
		current_stdio(&current_terminal->stdio);
        // if (current_terminal->input_handler == keyboard_handle_input)
        //     current_keyboard_handlers(&terminal_keyboard_handlers);
	}
	return current_terminal;
}

void terminal_clear(void)
{
	CURRENT_TERMINAL

	vga_fill(vga_entry(0, terminal->default_color));
	terminal->current_position = (t_vec2){0};
}

static int terminal_input_handler(t_key_scancode key_scancode)
{
	CURRENT_TERMINAL

	char control[128] = {0};

	get_sequence_from_scancode(key_scancode, &control);
	write(STDOUT, control, strlen(control));
	return 0;
}

// TODO: drop input handler
void terminal_init(t_vga_entry_color default_color, t_fp_input_handler input_handler)
{
	CURRENT_TERMINAL
	terminal->default_color = default_color;
	terminal->input_handler = terminal_input_handler;
	if (input_handler)
		terminal->input_handler = input_handler;
}