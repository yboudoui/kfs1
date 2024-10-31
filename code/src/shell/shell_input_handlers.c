#include "shell.h"

#include "codepage_437.h" // TODO: remove it

int shell_input_on_return(t_key_scancode key_scancode)
{
	CURRENT_SHELL

    readline_insert(codepage_437[key_scancode]);

    shell->current_working_buffer += 1;
    shell->current_working_buffer %= TERMINAL_READLINE_BUFFER_SIZE;

    size_t working_buffer = shell->current_working_buffer;

    readline_buffer_reset(&shell->readline_buffer[working_buffer]);
    current_readline_buffer(&shell->readline_buffer[working_buffer]);

    if (!vga_frame_move_cursor_down())
        shell_scroll_down();
    shell->terminal.vga_frame.cursor.x = 0;
    return 0;
}

int shell_input_on_button_up(t_key_scancode key_scancode)
{
    if (!vga_frame_move_cursor_up())
        shell_scroll_up();
    return 0;
}

int shell_input_on_button_down(t_key_scancode key_scancode)
{
    if (!vga_frame_move_cursor_down())
        shell_scroll_down();
    return 0;
}
