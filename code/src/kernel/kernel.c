#include "utils.h"
#include "keyboard_input_handlers.h"


int get_start_index(const char *str, char ch, int scrolling_depth)
{
    size_t i;
	for (i = 0; str[i] && scrolling_depth >= 1; i++)
	{
		if (str[i] == ch) {
			scrolling_depth--;
		}
	}
	return(i);
}

int get_end_index(const char *str, char ch, int start)
{
	int tmp=0;

	while(start < strlen(str) && tmp <25){
		if (str[start] == ch){
			tmp+=1;
		}
		start+=1;
	}
    return (start);
}

int get_char_occurences(const char *str, char ch)
{
	int nb = 0;
	for (size_t i = 0; str[i]; i++)
	{
		if (str[i] == ch) {
			nb += 1;
		}
	}
	return(nb);
}

static char buffers[2][2048];

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
	int start = get_start_index(terminal->readline_buffer.buffer, '\n',  *((int*)terminal->user_data));
	int end = get_end_index(terminal->readline_buffer.buffer, '\n', start);
    terminal_write_substring(
        terminal->readline_buffer.buffer,
        start,
		end
    );
    terminal_update();
    return 0;
}

#include "ft_printf.h"
void kernel_main(void)
{	
	VGA_ENABLE_CURSOR

	int scroll_index[2] = {0, 0};

	terminals[0] = (t_terminal){
	    .default_color = (t_vga_entry_color){
			.fg = VGA_COLOR_WHITE,
			.bg = VGA_COLOR_BLACK,
		},
	    .input_handler		= handlers,
		.readline_buffer	= {
			.max_size = 2048,
			.buffer = buffers[0],
		},
		.user_data = &scroll_index[0],
	};

	terminals[1] = (t_terminal){
	    .default_color = (t_vga_entry_color){
			.fg = VGA_COLOR_WHITE,
			.bg = VGA_COLOR_BLACK,
		},
	    .input_handler		= handlers,
		.readline_buffer	= {
			.max_size = 2048,
			.buffer = buffers[1],
		},
		.user_data = &scroll_index[1],
	};

	terminal_current(&terminals[0]);
	terminal_clear();
	ft_printf("%s %p", "hello", &terminals[0]);
	terminal_update();
	while (keyboard_handler(shell_get_character) == 0);
}