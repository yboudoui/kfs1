#include "utils.h"
#include "keyboard_input_handlers.h"

static t_terminal_input_handler handlers = {
    .default_handler = terminal_input_fallback,
    .handlers = {
        [KEY_ENTER]     = terminal_input_on_return,
        [KEY_BACKSPACE] = terminal_input_on_backspace,
        [KEY_DELETE]    = terminal_input_on_del,
        [KEY_LEFT]      = terminal_input_on_button_left,
        [KEY_RIGHT]     = terminal_input_on_button_right,
        [KEY_UP]        = terminal_input_on_button_up,
        [KEY_DOWN]      = terminal_input_on_button_down,
    }
};
static t_terminal terminals[2];

int shell_get_character(t_key_scancode key_scancode)
{
    if (key_scancode == KEY_1 || key_scancode == KEY_2) {
        terminal_current(&terminals[key_scancode - KEY_1]);
    } else {
    	terminal_handle_input(key_scancode);
	}

    terminal_reset_position();
    terminal_clear();
	CURRENT_TERMINAL

	t_terminal_readlines* 	readline =  &terminal->readline;
	t_readline_buffer*		tmp = NULL;
	size_t					position = 0;

	for (size_t i = readline->scroll_index; i < readline->scroll_index + VGA_HEIGHT; i++) {
		position = i % TERMINAL_READLINE_BUFFER_SIZE;
		tmp = &readline->readline_buffer[position];
		terminal_write(tmp->buffer, tmp->size);
	}
    terminal_update();
    return 0;
}

void kernel_main(void)
{	
	VGA_ENABLE_CURSOR
	terminals[0] = (t_terminal){
	    .default_color = (t_vga_entry_color){
			.fg = VGA_COLOR_WHITE,
			.bg = VGA_COLOR_BLACK,
		},
	    .input_handler		= handlers,
	};

	terminals[1] = (t_terminal){
	    .default_color = (t_vga_entry_color){
			.fg = VGA_COLOR_LIGHT_MAGENTA,
			.bg = VGA_COLOR_BLACK,
		},
	    .input_handler		= handlers,
	};

	terminal_current(&terminals[0]);
	terminal_clear();
	terminal_update();
	keyboard_handler(shell_get_character);
}