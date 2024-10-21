#include "terminal.h"

t_terminal* terminal_current(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		current_terminal = terminal;
	}
	return current_terminal;
}
