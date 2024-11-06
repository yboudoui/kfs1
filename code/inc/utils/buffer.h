#ifndef UTILS_BUFFER_H
#define UTILS_BUFFER_H

#include "memory.h"


typedef struct s_window {
    int start, end;
}   t_window;

t_window    window_from_position(int position, int relative);
size_t      window_size(t_window win);


typedef struct s_buffer {
    size_t  type_size;
    void*   data;
    size_t  len;
}   t_buffer;

void  buffer_remove(t_buffer* src, t_window window, const t_buffer fill);
void  buffer_insert(t_buffer* src, size_t position, const t_buffer fill);


#endif