#include "shell.h"
#include "codepage_437.h"

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

int shell_get_character(t_key_scancode key_scancode)
{
	shell();
    return 0;
}

void shell_init_color(t_vga_color foreground, t_vga_color background)
{
	CURRENT_SHELL
	terminal_init(
		(t_vga_entry_color){foreground, background},
		NULL
	);
}