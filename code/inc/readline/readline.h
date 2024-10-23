#ifndef READLINE_H
#define READLINE_H

#include <stddef.h>
#include "vectors.h"
#include "utils.h"

typedef struct {
    t_vec2          cursor_position;
    size_t          caret_position;
    size_t          size;
    size_t          max_size;
    char            *buffer;
} t_readline_buffer;

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer);
#define CURRENT_READLINE_BUFFER t_readline_buffer* readline_buffer = current_readline_buffer(NULL);

int     readline_update_caret_position(int n);
int     readline_is_character(char c, int position_relatif);
void    readline_insert(char c);
void    readline_remove(size_t nb);

#endif