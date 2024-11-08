#ifndef READLINE_H
#define READLINE_H

#include <stddef.h>
#include "vectors.h"
#include "utils.h"

#define READLINE_BUFFER_SIZE 1024

typedef struct {
    size_t  caret_position;
    DECLARE_BUFFER_TYPE(char, READLINE_BUFFER_SIZE) buffer;
} t_readline_buffer;

DECLARE_MEMSET(t_readline_buffer);

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer);
#define CURRENT_READLINE_BUFFER t_readline_buffer* readline_buffer = current_readline_buffer(NULL);

void    readline_buffer_reset(t_readline_buffer* readline_buffer);

void readline(void);

#endif