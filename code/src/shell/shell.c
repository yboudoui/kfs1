#include "shell.h"

t_shell* current_shell(t_shell* shell)
{
	static t_shell* current_shell = NULL;

	if (shell != NULL) {
        current_shell = shell;
	}
	terminal_current(&current_shell->terminal);
	return current_shell;
}

    char buffer[64];

int shell_get_character(char c)
{
    t_shell* shell = current_shell(NULL);
    shell->terminal.current_position = (t_vec2){0};

    terminal_handle_input(c);

    shell->buffer[shell->pos++] = c;
    
    terminal_clear();
    terminal_write(shell->buffer, shell->pos);
    terminal_update();
    return 0;
}