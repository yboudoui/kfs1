#ifndef SHELL_H
#define SHELL_H

#include "readline.h"
#include "terminal.h"

#define TERMINAL_READLINE_BUFFER_SIZE 27

typedef struct s_shell {
    t_terminal          terminal;
    t_readline_buffer   readline_buffer[TERMINAL_READLINE_BUFFER_SIZE];
    size_t              scroll_index;
    size_t              current_working_buffer;
}   t_shell;

t_shell* current_shell(t_shell* terminal);
#define CURRENT_SHELL t_shell* shell = current_shell(NULL);

void shell(void);


//
void shell_init_color(t_vga_color foreground, t_vga_color background);

#endif