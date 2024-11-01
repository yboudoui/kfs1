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

t_key_scancode get_scancode_from_sequence(const char* sequence)
{
    for (int i = 0; sequence_to_scancode[i].sequence != NULL; i++) {
        if (strcmp(sequence, sequence_to_scancode[i].sequence) == 0) {
            return sequence_to_scancode[i].scancode;
        }
    }
    return -1;  // Indicate no match
}

static int terminal_input_handler(t_key_scancode key_scancode)
{
	CURRENT_TERMINAL

	char* control = NULL;

	control = sequence_to_scancode[key_scancode];
	if (control == NULL) {
		control = codepage_437[key_scancode];
	}
	if (control)
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