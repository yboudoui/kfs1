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
	vga_fill(vga_entry(' ', terminal->default_color));
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
	terminal->input_handler = input_handler ? input_handler : terminal_input_handler;

	vga_frame_init(&terminal->vga_frame);
	vga_fill(vga_entry(' ', default_color));
}

DECLARE_BUFFER_INSERT(char)
DECLARE_BUFFER_REMOVE(char)

static void on_backspace(char c)
{
	CURRENT_TERMINAL
	if (terminal->caret_position <= 0) return;

	int len = (terminal->buffer.data[terminal->caret_position - 1] == '\t') ? -TABSIZE : -1;

	m_buffer_remove(char)(
		&terminal->buffer,
		window_from_position(terminal->caret_position, 1),
		(t_buffer){1, 0, " "}
	);
	terminal->caret_position -= 1;

	vga_frame_remove(len, vga_entry(' ', terminal->default_color));
	vga_frame_move_cursor_position_by(len);
}

static void on_delete(char c)
{
	CURRENT_TERMINAL

	m_buffer_remove(char)(
		&terminal->buffer,
		window_from_position(terminal->caret_position, 1),
		(t_buffer){1, 0, " "}
	);

	int len;
	switch (terminal->buffer.data[terminal->caret_position])
	{
	case '\t':
		len = TABSIZE;
		break;
	default:
		len = 1;
		break;
	}
	vga_frame_remove(len, vga_entry(' ', terminal->default_color));
}

static void on_default(char c)
{
	CURRENT_TERMINAL

	t_buffer buffer = {TERMINAL_BUFFER_SIZE, terminal->buffer.size, terminal->buffer.data};
	m_buffer_insert_one(char)(&buffer, terminal->caret_position, c);
	terminal->buffer.size = buffer.size;
	terminal->caret_position += 1;

	if (c == '\t') {
		for (size_t i = 0; i < TABSIZE; i++)
			vga_frame_put_entry(vga_entry(' ', terminal->default_color));
		vga_frame_move_cursor_position_by(+TABSIZE);
	}
	else {
		vga_frame_put_entry(vga_entry(c, terminal->default_color));
		vga_frame_move_cursor_position_by(+1);
	}
}

static void on_enter(char c)
{
		printk("loo\bl\033[2J");

}

static bool loot_at(int nb, char c)
{
	CURRENT_TERMINAL
	return terminal->buffer.data[terminal->caret_position + nb] == c;
}

static void on_cursor_mouvement(t_vec2 mouvement)
{
	CURRENT_TERMINAL

	if (terminal->caret_position == terminal->buffer.size && mouvement.x > 0) return;

    int sign = (mouvement.x < 0) ? -1 : 1;
	int len = mouvement.x * sign;

    // TODO: check limit
    for (size_t i = 0; i < len; i++)
    {
		int index = (sign * i);
		index -= (sign < 0);
		vga_frame_move_cursor_position_by(sign * (loot_at(index, '\t') ? TABSIZE : 1));
    }
	terminal->caret_position += mouvement.x;
}

int terminal_write(const char* buffer, size_t size)
{
	static t_ecma48_handlers handlers = {
		.on_cursor_mouvement	= on_cursor_mouvement,
		.on_clear_screen		= terminal_clear,
		.default_char_handler	= on_default,
		.char_handlers = {
			['\b']      		= on_backspace,
			['\177']    		= on_delete,
			['\n']				= on_enter,
		}
	};
	ecma48_hooks(buffer, size, &handlers);
	return size;
}

void	terminal_update(void)
{
    char  	read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t	read_size = read(STD_OUT, read_buffer, STD_IO_BUFFER_SIZE);
	terminal_write(read_buffer, read_size);
	vga_main_frame_update();
}