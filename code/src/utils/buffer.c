#include "buffer.h"

t_window window_from_position(int position, int relative)
{
    if (relative < 0)
        return (t_window){position + relative, position};
    return (t_window){position, position + relative};
}

size_t window_size(t_window win)
{
    return win.end - win.start;
}

void  buffer_remove(t_buffer* src, t_window window, const t_buffer fill)
{
    if (window.start > window.end) return ;
    if (src->type_size != fill.type_size) return;
    
    size_t          type_size;
    size_t          len, fill_len;
    unsigned char   *buffer, *fill_buffer;
    
    type_size       = src->type_size;
    buffer          = src->data;
    len             = type_size * src->len;
    window.start    = type_size * window.start;
    window.end      = type_size * window.end;
    fill_buffer     = fill.data;
    fill_len        = type_size * fill.len;

    memmove(
        buffer + window.start,
        buffer + window.end,
        len - window.end);

    size_t index_fill = 0;
    size_t index = (len - window_size(window));

    while (index < len)
    {
        index_fill %= fill_len;
        buffer[index] = fill_buffer[index_fill];
        index_fill  += 1;
        index       += 1;
    }
}

void  buffer_insert(t_buffer* src, size_t position, const t_buffer fill)
{
    if (position > src->len) return;
    if (src->type_size != fill.type_size) return;
    
    size_t          type_size;
    size_t          len, fill_len;
    unsigned char   *buffer, *fill_buffer;
    
    type_size       = src->type_size;
    buffer          = src->data;
    len             = type_size * src->len;
    position        = type_size * position;
    fill_buffer     = fill.data;
    fill_len        = type_size * fill.len;

    memmove(
        buffer + position + fill_len,
        buffer + position,
        len - (position + fill_len));

    size_t index_fill = 0;
    size_t index = position;

    while (index < position + fill_len)
    {
        index_fill %= fill_len;
        buffer[index] = fill_buffer[index_fill];
        index_fill  += 1;
        index       += 1;
    }
}
