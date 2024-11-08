#include "terminal.h"

t_terminal* current_terminal(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		current_terminal = terminal;
		current_terminal->buffer.len = TERMINAL_BUFFER_SIZE;
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


DECLARE_BUFFER_INSERT(char)
DECLARE_BUFFER_REMOVE(char)

static void on_backspace(char c)
{
	CURRENT_TERMINAL

	t_vga_entry default_vga_entry = vga_entry(' ', terminal->default_color);


	if (terminal->caret_position <= 0) return;

	int len = -1;
	if (terminal->buffer.data[terminal->caret_position - 1] == '\t')
		len = -TABSIZE;

	vga_frame_remove(len, default_vga_entry);
	m_buffer_remove(char)(
		&terminal->buffer,
		window_from_position(terminal->caret_position, -1),
		(t_buffer){1, " "}
	);

	terminal->caret_position -= 1;
	vga_frame_move_cursor_position_by(len);
}

static void on_delete(char c)
{
	CURRENT_TERMINAL

	t_vga_entry default_vga_entry = vga_entry(' ', terminal->default_color);

	vga_frame_remove(1, default_vga_entry);
	m_buffer_remove(char)(
		&terminal->buffer,
		window_from_position(terminal->caret_position, -1),
		(t_buffer){1, " "}
	);
}

static void on_default(char c)
{
	CURRENT_TERMINAL

	m_buffer_insert_one(char)(&terminal->buffer, terminal->caret_position, c);
	terminal->caret_position += 1;
	int move_by = +1;
	if (c == '\t') move_by = +TABSIZE;
	else vga_frame_put_entry(vga_entry(c, terminal->default_color));
	vga_frame_move_cursor_position_by(move_by);
}

static void on_cursor_mouvement(t_vec2 mouvement)
{
	CURRENT_TERMINAL
	terminal->caret_position += mouvement.x;
	vga_frame_move_cursor_position_by(mouvement.x);
}

static t_ecma48_handlers handlers = {
    .on_cursor_mouvement = on_cursor_mouvement,
    .default_char_handler = on_default,
    .char_handlers = {
        ['\b']      = on_backspace,
        ['\177']    = on_delete, 
    }
};

void	terminal_update(void)
{
    char                read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t              read_size = read(STD_OUT, read_buffer, STD_IO_BUFFER_SIZE);
    for (size_t i = 0; i < read_size; i += ecma48_hooks(&read_buffer[i], &handlers));
	vga_main_frame_update();
}