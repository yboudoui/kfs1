#ifndef UTILS_BUFFER_H
#define UTILS_BUFFER_H

#include "memory.h"


typedef struct s_window {
    int start, end;
}   t_window;

t_window    window_from_position(int position, int relative);
size_t      window_size(t_window win);


typedef struct s_buffer {
    void*   data;
    size_t  len;
}   t_buffer;

#define DECLARE_BUFFER_INSERT(type)                                                     \
DECLARE_MEMMOVE(type)                                                                   \
static void buffer_insert_##type(t_buffer* src, size_t position, const t_buffer fill) { \
    if (position > src->len) return;                                                    \
    memmove(type)(                                                                      \
        ((type*)(src->data)) + position + fill.len,                                     \
        ((type*)(src->data)) + position,                                                \
        src->len - (position + fill.len));                                              \
    size_t index_fill = 0;                                                              \
    for (size_t index = position; index < position + fill.len; index++) {               \
        index_fill      %= fill.len;                                                    \
        ((type*)(src->data))[index]   = ((type*)(fill.data))[index_fill++];             \
    }                                                                                   \
    src->len += fill.len;                                                               \
}


#define m_buffer_insert(type) buffer_insert_##type

#define DECLARE_BUFFER_REMOVE(type)                                                     \
static void buffer_remove_##type(t_buffer* src, t_window window, const t_buffer fill) { \
    if (window.start > window.end) return ;                                             \
    size_t          win_size        = window_size(window);                              \
    memmove(type)(                                                                      \
        ((type*)(src->data)) + window.start,                                            \
        ((type*)(src->data)) + window.end,                                              \
        src->len - window.end);                                                         \
    size_t index_fill = 0;                                                              \
    for (size_t index = (src->len - win_size); index < src->len; index++) {             \
        index_fill %= fill.len;                                                         \
        ((type*)(src->data))[index] = ((type*)(fill.data))[index_fill++];               \
    }                                                                                   \
    src->len -= win_size;                                                               \
}

#define m_buffer_remove(type) buffer_remove_##type


#endif