#include "shell.h"

t_shell shell_init(t_vga_entry_color colors)
{
    t_shell shell = {};

	shell.terminal_frame = (t_terminal_frame){
        .default_color = colors
    };

    memset(0, shell.buffer, VGA_MAX_PRINTABLE_CHARACTER);
    return shell;
}


t_shell* current_shell(t_shell* shell)
{
	static t_shell* current_shell;
	if (shell != NULL) {
		current_shell = shell;
		current_terminal_frame(&current_shell->terminal_frame);
	}
	return current_shell;
}

int shell_get_character(char c)
{
    t_shell* shell = current_shell(NULL);
    
    shell->buffer[shell->pos++] = c;
    terminal_clear();
    terminal_reset_position();
    terminal_writestring(shell->buffer);
    terminal_update_frame();
    return 0;
}