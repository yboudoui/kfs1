#ifndef READLINE_H
#define READLINE_H

#include <stddef.h>
#include "vectors.h"
#include "utils.h"

// Define t_readline_buffer with proper alignment
typedef struct {
    t_vec2          cursor_position;
    size_t          caret_position;
    size_t          size;
    const size_t    max_size;
    char            *buffer; // Pointer for dynamic allocation
} __attribute__((packed, aligned(4))) t_readline_buffer;

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer);
#define CURRENT_READLINE_BUFFER t_readline_buffer* readline_buffer = current_readline_buffer(NULL);

// Macro to create a readline buffer with a given size
#define NEW_READLINE_BUFFER(buffer_size) \
    (t_readline_buffer)({ \
        struct { \
            t_vec2          cursor_position; \
            size_t          caret_position; \
            size_t          size; \
            const size_t    max_size; \
            char            buffer[buffer_size]; \
        } __attribute__((packed, aligned(4))) tmp = { .max_size = buffer_size    }; \
        *((t_readline_buffer*)&tmp); \
    })

/*
*   To move caret by n character to the left put -n and to the right +n
*/

int     readline_update_caret_position(int n);
int     readline_is_character(char c, int position_relatif);
void    readline_insert(char c);
void    readline_remove(size_t nb);

#endif