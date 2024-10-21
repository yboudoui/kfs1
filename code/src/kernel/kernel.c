#include "utils.h"
#include "shell.h"

#define TABSIZE 4

int terminal_input_fallback(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);
    shell->terminal.vga_frame.cursor.x += 1;
    shell->buffer[shell->pos++] = codepage_437[key_scancode];
    return 0;
}

int terminal_input_on_return(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);
    shell->terminal.vga_frame.cursor.x = 0;
    shell->terminal.vga_frame.cursor.y += 1;
    shell->buffer[shell->pos++] = codepage_437[key_scancode];
    return 0;
}

int terminal_input_on_backspace(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->pos -= 1;
    if (shell->buffer[shell->pos] == '\n') {
        shell->terminal.vga_frame.cursor.y -= 1;
        shell->terminal.vga_frame.cursor.x = shell->pos;
    } else {
        shell->terminal.vga_frame.cursor.x -= 1;
    }
    shell->buffer[shell->pos] = ' ';
    return 0;
}

int terminal_input_on_del(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    return 0;
}

int terminal_input_on_tab(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->terminal.vga_frame.cursor.x += TABSIZE;
    for (size_t i = 0; i < TABSIZE; i++) {
        shell->buffer[shell->pos++] = ' ';
    }
    return 0;
}

int terminal_input_on_button_left(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->terminal.vga_frame.cursor.x -= 1;
    return 0;
}

int terminal_input_on_button_right(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->terminal.vga_frame.cursor.x += 1;
    return 0;
}

int terminal_input_on_button_up(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->terminal.vga_frame.cursor.y -= 1;
    return 0;
}

int terminal_input_on_button_down(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->terminal.vga_frame.cursor.y += 1;
    return 0;
}


void kernel_main(void) 
{
	VGA_ENABLE_CURSOR
	t_shell shell = {
        .buffer = {' '},
	    .terminal = (t_terminal){
            .default_color = (t_vga_entry_color){
				.fg = VGA_COLOR_WHITE,
				.bg = VGA_COLOR_BLACK,
			},
            .default_handler = terminal_input_fallback,
            .handlers = {
                [KEY_ENTER]     = terminal_input_on_return,
                [KEY_BACKSPACE] = terminal_input_on_backspace,
                [KEY_TAB]       = terminal_input_on_tab,
                [KEY_DELETE]    = terminal_input_on_del,
                [KEY_LEFT]      = terminal_input_on_button_left,
                [KEY_RIGHT]     = terminal_input_on_button_right,
                [KEY_UP]        = terminal_input_on_button_up,
                [KEY_DOWN]      = terminal_input_on_button_down,
            },
        },
    };
	current_shell(&shell);
	terminal_clear();
	terminal_update();

	while (keyboard_handler(shell_get_character) == 0);
}