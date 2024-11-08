#include "shell.h"

#include "codepage_437.h" // TODO: remove it

static void shell_scrool(void)
{
	CURRENT_SHELL
	t_readline_buffer*		tmp = NULL;

	size_t start = shell->scroll_index;
	size_t end = start + VGA_HEIGHT;

    // terminal_clear();
	while (start < end)
	{
		tmp = &shell->readline_buffer[start % TERMINAL_READLINE_BUFFER_SIZE];
		terminal_write(tmp->buffer.data, tmp->buffer.size);
		start += 1;
	}
}

int shell_input_on_return(t_key_scancode key_scancode)
{
	CURRENT_SHELL

    // readline_insert(codepage_437[key_scancode]);

    shell->current_working_buffer += 1;
    shell->current_working_buffer %= TERMINAL_READLINE_BUFFER_SIZE;

    size_t working_buffer = shell->current_working_buffer;

    readline_buffer_reset(&shell->readline_buffer[working_buffer]);
    current_readline_buffer(&shell->readline_buffer[working_buffer]);

    if (!vga_frame_move_cursor_down())
        shell->scroll_index += 1;
    shell->terminal.vga_frame.cursor.x = 0;
    vga_frame_update_caret();
    return 0;
}

int shell_input_on_button_up(t_key_scancode key_scancode)
{
    CURRENT_SHELL
    if (!vga_frame_move_cursor_up()) {
        if(shell->scroll_index) {
            shell->scroll_index -= 1;
            shell_scrool();
        }
    }
    return 0;
}

int shell_input_on_button_down(t_key_scancode key_scancode)
{
	CURRENT_SHELL

    if (!vga_frame_move_cursor_down()) {
        shell->scroll_index += 1;
        shell_scrool();
    }
    return 0;
}
