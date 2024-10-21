#include "shell.h"

t_shell* current_shell(t_shell* shell)
{
	static t_shell* current_shell = NULL;

	if (shell != NULL) {
        current_shell = shell;
	    terminal_current(&current_shell->terminal);
	}
	return current_shell;
}

    char buffer[64];

int shell_get_character(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    terminal_handle_input(key_scancode);
     
    shell->terminal.current_position = (t_vec2){0};
    terminal_clear();
    terminal_write_number(ITOA_BASE_DECIMAL, key_scancode);
    terminal_putchar('\n');
    terminal_write_number(ITOA_BASE_HEXADECIMAL, key_scancode);
    terminal_write(shell->buffer, shell->pos);
    terminal_update();
    return 0;
}