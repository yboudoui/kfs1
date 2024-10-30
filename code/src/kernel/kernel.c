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

void shell(void)
{
	CURRENT_TERMINAL
	t_terminal_readlines* 	readline =  &terminal->readline;
	t_readline_buffer*		tmp = NULL;

	size_t start = readline->scroll_index;
	size_t end = start + VGA_HEIGHT;


	while (start < end)
	{
		tmp = &readline->readline_buffer[start % TERMINAL_READLINE_BUFFER_SIZE];
		// printf("%d %d\n", start % TERMINAL_READLINE_BUFFER_SIZE, readline->current_working_buffer);
		terminal_write(tmp->buffer, tmp->size);
		start += 1;
	}

}

int shell_get_character(t_key_scancode key_scancode)
{
    if (key_scancode == KEY_1 || key_scancode == KEY_2) {
        terminal_current(&terminals[key_scancode - KEY_1]);
    } else {
    	terminal_handle_input(key_scancode);
	}

	CURRENT_TERMINAL
    terminal_clear();
	shell();
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
	    .input_handler = handlers,
	};

	terminals[1] = (t_terminal){
	    .default_color = (t_vga_entry_color){
			.fg = VGA_COLOR_LIGHT_MAGENTA,
			.bg = VGA_COLOR_BLACK,
		},
	    .input_handler = handlers,
	};

	terminal_current(&terminals[0]);
	terminal_clear();
	terminal_update();
	keyboard_handler(shell_get_character);
}