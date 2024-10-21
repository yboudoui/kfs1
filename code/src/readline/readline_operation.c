#include "readline.h"

static int update_caret_position(int n)
{
    CURRENT_READLINE_BUFFER

    int  new_position   = readline_buffer->caret_position + n;
    int  old_position   = new_position;

    if (new_position < 0)
        new_position = 0;
    if (new_position > readline_buffer->max_size)
        new_position = readline_buffer->max_size;

    readline_buffer->caret_position = new_position;
    return (old_position - new_position);
}

// readline_move_left = update_caret_position(-n)
// readline_move_right = update_caret_position(+n)

void terminal_insert(char c)
{
    CURRENT_READLINE_BUFFER

    size_t  position        = readline_buffer->caret_position;
    char*   buffer_position = readline_buffer->buffer + position;

    memmove(
        buffer_position + 1,
        buffer_position,
        readline_buffer->size - readline_buffer->caret_position + 1
    );

    readline_buffer->buffer[readline_buffer->caret_position] = c;
    update_caret_position(+1);
    readline_buffer->size += 1;
}

void terminal_remove(int nb)
{
    CURRENT_READLINE_BUFFER

    size_t  position        = readline_buffer->caret_position;
    char*   buffer_position = readline_buffer->buffer + position;

    memmove(
        buffer_position - nb,
        buffer_position,
        readline_buffer->size - readline_buffer->caret_position + 1
    );
    update_caret_position(-nb);
    readline_buffer->size -= nb;
}