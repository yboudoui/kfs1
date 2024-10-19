#ifndef READLINE_H
#define READLINE_H

#include "keyboard.h"

typedef int (*t_fp_get_character)(char c);
void readline(t_fp_get_character handler);

#endif