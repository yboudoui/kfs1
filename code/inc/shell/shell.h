#ifndef SHELL_H
#define SHELL_H

#include "terminal.h"
#include "keyboard.h"
#include "utils.h"

typedef struct {
    t_terminal  terminal;
    char        **commandes;
	size_t      pos;
    char        buffer[VGA_MAX_PRINTABLE_CHARACTER];
} t_shell;

t_shell*    current_shell(t_shell* shell);

int         shell_get_character(t_key_scancode key_scancode);

#endif