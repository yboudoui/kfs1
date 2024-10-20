#include "shell.h"

t_shell shell_init(t_vga_entry_color colors)
{
    t_shell shell = {
	    .terminal = (t_terminal){
            .default_color = colors
        },
    };
    memset(char)(shell.buffer, ' ', VGA_MAX_PRINTABLE_CHARACTER);
    return shell;
}

t_shell* current_shell(t_shell* shell)
{
	static t_shell* current_shell = NULL;

	if (shell != NULL) {
		current_shell = shell;
	}
	terminal_current(&current_shell->terminal);
	return current_shell;
}

int shell_get_character(char c)
{
    t_shell*    shell;
    
    shell = current_shell(NULL);
    shell->terminal.current_position = (t_vec2){0};
    terminal_clear(&shell->terminal);


    if (c == '\n') {
        shell->terminal.vga_frame.cursor.x = 0;
        shell->terminal.vga_frame.cursor.y += 1;
        // terminal_return(&shell->terminal);
    } else {
        shell->terminal.vga_frame.cursor.x += 1;
    }
    shell->buffer[shell->pos++] = c;
    

    

    // terminal_reset_position();
     // terminal_write_string(&shell->terminal, "Hello\nWorld");

    terminal_write(&shell->terminal, shell->buffer, shell->pos);

	vga_main_frame_update(shell->terminal.vga_frame);
    return 0;
}