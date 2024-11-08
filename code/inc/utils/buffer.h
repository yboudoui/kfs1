#ifndef UTILS_BUFFER_H
#define UTILS_BUFFER_H

#include "memory.h"


typedef struct s_window {
    int start, end;
}   t_window;

t_window    window_from_position(int position, int relative);
size_t      window_size(t_window win);

struct s_buffer {
    size_t  len;
    size_t  size;
    void*   data;
};
typedef  struct s_buffer  t_buffer;
                          
#define DECLARE_BUFFER_TYPE(type, size_lol) \
struct {                    \
    size_t  len;            \
    size_t  size;           \
    type    data[size_lol];     \
}


#define DECLARE_BUFFER_INSERT(type)                                                     \
DECLARE_MEMMOVE(type)                                                                   \
static void buffer_insert_##type(t_buffer* src, size_t position, const t_buffer fill) { \
    t_buffer* buffer = (t_buffer*)src;                                                  \
    if (position > buffer->len) return;                                                 \
    memmove(type)(                                                                      \
        ((type*)(buffer->data)) + position + fill.len,                                  \
        ((type*)(buffer->data)) + position,                                             \
        buffer->len - (position + fill.len));                                           \
    size_t index_fill = 0;                                                              \
    for (size_t index = position; index < position + fill.len; index++) {               \
        index_fill      %= fill.len;                                                    \
        ((type*)(buffer->data))[index]   = ((type*)(fill.data))[index_fill++];          \
    }                                                                                   \
    buffer->size += fill.len;                                                           \
}                                                                                       \
static void buffer_insert_one_##type(void* src, size_t position, type fill) {           \
    buffer_insert_##type(src, position, (t_buffer){.len = 1, .data = (type[]){fill}});  \
}

#define m_buffer_insert(type) buffer_insert_##type
#define m_buffer_insert_one(type) buffer_insert_one_##type



#define DECLARE_BUFFER_REMOVE(type)                                                     \
static void buffer_remove_##type(void* src, t_window window, const t_buffer fill) {     \
    t_buffer* buffer = src;                                                             \
    if (window.start > window.end) return ;                                             \
    size_t          win_size        = window_size(window);                              \
    memmove(type)(                                                                      \
        ((type*)(buffer->data)) + window.start,                                         \
        ((type*)(buffer->data)) + window.end,                                           \
        buffer->len - window.end);                                                      \
    size_t index_fill = 0;                                                              \
    for (size_t index = (buffer->len - win_size); index < buffer->len; index++) {       \
        index_fill %= fill.len;                                                         \
        ((type*)(buffer->data))[index] = ((type*)(fill.data))[index_fill++];            \
    }                                                                                   \
    buffer->size -= win_size;                                                           \
}

#define m_buffer_remove(type) buffer_remove_##type


#endif