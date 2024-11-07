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
	vga_fill(vga_entry(' ', default_color));
	if (input_handler)
		terminal->input_handler = input_handler;
}


DECLARE_BUFFER_INSERT(t_vga_entry)
DECLARE_BUFFER_REMOVE(t_vga_entry)
DECLARE_BUFFER_INSERT(char)
DECLARE_BUFFER_REMOVE(char)


void	terminal_update(void)
{
	char	read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t	read_size = read(STD_OUT, read_buffer, STD_IO_BUFFER_SIZE);


	CURRENT_TERMINAL

	t_ecma48_sequence 	seq = {0};
	size_t index = 0;

	t_buffer buffer = {
		.data		= terminal->buffer,
		.len		= TERMINAL_BUFFER_SIZE,
	};

	t_buffer vga = {
		.data		= terminal->vga_frame.buffer,
		.len		= VGA_MAX_PRINTABLE_CHARACTER,
	};

	t_vga_entry default_vga_entry, character;
	default_vga_entry = vga_entry(' ', terminal->default_color);

	t_buffer fill = {
		.len		= 1
	};

	while (index < read_size)
	{
		index += ecma48_parse_sequence(&read_buffer[index], &seq);

		if (seq.is_controle) {
			terminal->caret_position += seq.cursor_movement.x;
			vga_frame_move_cursor_position_by(seq.cursor_movement.x);
			continue;
		}

		switch (seq.character)
		{
			case '\t':
				character =  vga_entry(seq.character, terminal->default_color);
				fill.data = &character;
				m_buffer_insert(t_vga_entry)(
					&vga,
					terminal->caret_position,
					fill
				);
				m_buffer_insert(char)(
					&buffer,
					terminal->caret_position,
					(t_buffer){"\t", 1}
				);

				terminal->caret_position += 1;
				vga_frame_move_cursor_position_by(+TABSIZE);
				break;
			case '\b':
				if (terminal->caret_position <= 0)
					break;
				int len = -1;
				if (terminal->buffer[terminal->caret_position - 1] == '\t')
					len = -TABSIZE;
				fill.data = &default_vga_entry;

				m_buffer_remove(t_vga_entry)(
					&vga,
					window_from_position(terminal->caret_position, len),
					fill
				);
				m_buffer_remove(char)(
					&buffer,
					window_from_position(terminal->caret_position, -1),
					(t_buffer){" ", 1}
				);

				terminal->caret_position -= 1;
				vga_frame_move_cursor_position_by(len);
				break;
			case '\177':
				fill.data = &default_vga_entry;
				m_buffer_remove(t_vga_entry)(
					&vga,
					window_from_position(terminal->caret_position, 1),
					fill
				);
				m_buffer_remove(char)(
					&buffer,
					window_from_position(terminal->caret_position, -1),
					(t_buffer){" ", 1}
				);
				break;
			default:
				character =  vga_entry(seq.character, terminal->default_color);
				fill.data = &character;
				m_buffer_insert(t_vga_entry)(
					&vga,
					terminal->caret_position,
					fill
				);
				m_buffer_insert(char)(
					&buffer,
					terminal->caret_position,
					(t_buffer){(char[]){seq.character}, 1}
				);
				terminal->caret_position += 1;
				vga_frame_move_cursor_position_by(+1);
				break;
		}
	}
	vga_main_frame_update();
}
