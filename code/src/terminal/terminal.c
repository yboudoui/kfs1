#include "terminal.h"

t_terminal* current_terminal(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		current_terminal = terminal;
        current_vga_frame(&current_terminal->vga_frame);
		current_keyboard_handler(current_terminal->input_handler);
		current_stdio(&current_terminal->stdio);
	}
	return current_terminal;
}

void terminal_clear(void)
{
	CURRENT_TERMINAL

	vga_fill(vga_entry(0, terminal->default_color));
	terminal->caret_position = 0;
}

static int terminal_input_handler(t_key_scancode key_scancode)
{
	static char* ops[] = {
	    [KEY_UP]    = "\033[%dA",
	    [KEY_DOWN]  = "\033[%dB",
	    [KEY_RIGHT] = "\033[%dC",
	    [KEY_LEFT]  = "\033[%dD",
	    NULL,
	};

    if(ops[key_scancode] != NULL)
        dprintf(STD_IN, ops[key_scancode], 1);
    else
        dprintf(STD_IN, "%c", codepage_437[key_scancode]);
	return 0;
}

// TODO: drop input handler
void terminal_init(t_vga_entry_color default_color, t_fp_input_handler input_handler)
{
	CURRENT_TERMINAL

	(*terminal) = (t_terminal){0};
	terminal->default_color = default_color;
	terminal->input_handler = terminal_input_handler;
	if (input_handler)
		terminal->input_handler = input_handler;
}

void	terminal_update(void)
{
	char	read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t	read_size;

	read_size = read(STD_OUT, read_buffer, STD_IO_BUFFER_SIZE);

	terminal_write_2(read_buffer, read_size);
	vga_main_frame_update();
}
