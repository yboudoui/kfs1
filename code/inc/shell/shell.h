#ifndef SHELL_H
#define SHELL_H

#include "terminal.h"
#include "keyboard.h"
#include "utils.h"

typedef struct {
    t_terminal  terminal;
    char        **commandes;
} t_shell;


t_shell* current_shell(t_shell* shell);
#define CURRENT_SHELL t_shell* shell = current_shell(NULL);

int         shell_get_character(t_key_scancode key_scancode);

#endif