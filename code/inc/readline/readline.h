#ifndef READLINE_H
#define READLINE_H

#include <stddef.h>
#include "vectors.h"

typedef struct {

} t_readline;

// Define t_readline_buffer with proper alignment
typedef struct {
    t_vec2 cursor_position;
    size_t caret_position;
    size_t buffer_size;
    char *buffer; // Pointer for dynamic allocation
} __attribute__((packed, aligned(4))) t_readline_buffer;

// Macro to create a readline buffer with a given size
#define NEW_READLINE_BUFFER(size) \
    ({ \
        struct { \
            t_vec2          cursor_position; \
            size_t          caret_position; \
            const size_t    buffer_size; \
            const char      buffer[size]; \
        } __attribute__((packed, aligned(4))) tmp = { .buffer_size = size }; \
        *((t_readline_buffer*)&tmp); \
    })

// t_readline_buffer buffer_one = NEW_READLINE_BUFFER(2048);

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer);

#define CURRENT_READLINE_BUFFER t_readline_buffer* readline_buffer = current_readline_buffer(NULL);

#endif