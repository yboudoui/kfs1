#include "shell.h"

t_shell* current_shell(t_shell* shell)
{
	static t_shell* current_shell = NULL;

	if (shell != NULL) {
        current_shell = shell;
	    terminal_current(&current_shell->terminal);
	}
	return current_shell;
};

int shell_get_character(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    terminal_reset_position();
    terminal_clear();

    terminal_handle_input(key_scancode);
     
    terminal_write(shell->terminal.readline_buffer.buffer , shell->terminal.readline_buffer.size);
    terminal_update();
    return 0;
}