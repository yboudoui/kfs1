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
