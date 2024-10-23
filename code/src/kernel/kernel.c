#include "utils.h"
#include "terminal.h"
#include "keyboard.h"


#include "keyboard_input_handlers.h"

static char buffers_one[2048];
static char buffers_two[2048];

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
    }

    CURRENT_TERMINAL	

    terminal_handle_input(key_scancode);

    terminal_reset_position();
    terminal_clear();
    terminal_write(
        terminal->readline_buffer.buffer,
        terminal->readline_buffer.size
    );
    terminal_update();
    return 0;
}

void kernel_main(void)
{	
	VGA_ENABLE_CURSOR

	terminals[0] = (t_terminal){
	    .default_color = (t_vga_entry_color){
			.fg = VGA_COLOR_WHITE,
			.bg = VGA_COLOR_CYAN,
		},
	    .input_handler		= handlers,
		.readline_buffer	= {
			.max_size = 2048,
			.buffer = buffers_one,
		},
	};

	terminals[1] = (t_terminal){
	    .default_color = (t_vga_entry_color){
			.fg = VGA_COLOR_WHITE,
			.bg = VGA_COLOR_BLACK,
		},
	    .input_handler		= handlers,
		.readline_buffer	= {
			.max_size = 2048,
			.buffer = buffers_two,
		},
	};

	terminal_current(&terminals[0]);
	terminal_clear();
	terminal_update();
	while (keyboard_handler(shell_get_character) == 0);
}