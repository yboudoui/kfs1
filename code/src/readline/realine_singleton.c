#include "readline.h"

t_readline readline_current(void)
{
	static t_readline current_readline = {};

	return current_readline;
}

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer)
{
	static t_readline_buffer* current_readline_buffer = NULL;

	if (readline_buffer != NULL) {
		current_readline_buffer = readline_buffer;
	}
	return current_readline_buffer;
}
