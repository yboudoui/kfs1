#ifndef READLINE_H
#define READLINE_H

#include <stddef.h>
#include "vectors.h"
#include "utils.h"

#define READLINE_BUFFER_SIZE 1024

#define TABSIZE 4

typedef void (*t_fp_move_cursor_by)(int);

#include "cursor.h"
static t_fp_move_cursor_by move_cursor = vga_frame_move_cursor_position_by;

typedef struct {
    int     cursor_movement;
    size_t  caret_position;
    
    size_t  size;
    char    buffer[READLINE_BUFFER_SIZE];
} t_readline_buffer;

DECLARE_MEMSET(t_readline_buffer);

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer);
#define CURRENT_READLINE_BUFFER t_readline_buffer* readline_buffer = current_readline_buffer(NULL);

void    readline_insert(char c);
void    readline_remove(int nb);

void    readline_buffer_reset(t_readline_buffer* readline_buffer);
#endif