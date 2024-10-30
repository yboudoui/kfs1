#include "shell.h"

t_shell* current_shell(t_shell* shell)
{
	static t_shell* current_shell = NULL;
    size_t working_buffer;

	if (shell != NULL) {
		current_shell = shell;
        current_terminal(&current_shell->terminal);
        working_buffer = current_shell->current_working_buffer;
	    current_readline_buffer(&current_shell->readline_buffer[working_buffer]);
	}
	return current_shell;
}

void shell(void)
{
	CURRENT_SHELL
	t_readline_buffer*		tmp = NULL;

	size_t start = shell->scroll_index;
	size_t end = start + VGA_HEIGHT;

	while (start < end)
	{
		tmp = &shell->readline_buffer[start % TERMINAL_READLINE_BUFFER_SIZE];
		terminal_write(tmp->buffer, tmp->size);
		start += 1;
	}
}

void shell_scroll_up(void)
{
	CURRENT_SHELL

    if(shell->scroll_index)
       shell->scroll_index -= 1;
}

void shell_scroll_down(void)
{
	CURRENT_SHELL
    shell->scroll_index += 1;
}

void shell_next_line(void)
{
	CURRENT_SHELL

    shell->current_working_buffer += 1;
    shell->current_working_buffer %= TERMINAL_READLINE_BUFFER_SIZE;

    size_t working_buffer = shell->current_working_buffer;

    readline_buffer_reset(&shell->readline_buffer[working_buffer]);
    current_readline_buffer(&shell->readline_buffer[working_buffer]);

    if (!move_cursor_down())
        shell_scroll_down();
    shell->terminal.vga_frame.cursor.x = 0;
}