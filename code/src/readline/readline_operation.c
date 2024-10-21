#include "readline.h"

static int update_caret_position(int n)
{
    CURRENT_READLINE_BUFFER

    size_t  position = readline_buffer->caret_position;
    size_t  old_position = position;

    if (position + n < 0)
        position = 0;
    if (position + n > readline_buffer->buffer_size)
        position = readline_buffer->buffer_size;

    readline_buffer->caret_position = position;
    return (old_position - position);
}

// readline_move_left = update_caret_position(-n)
// readline_move_right = update_caret_position(+n)

void terminal_insert(char c)
{
    CURRENT_READLINE_BUFFER

    memmove(
        &readline_buffer->buffer[readline_buffer->caret_position + 1],
        &readline_buffer->buffer[readline_buffer->caret_position],
        readline_buffer->buffer_size - readline_buffer->caret_position + 1
    );
    shell->buffer[readline_buffer->caret_position++] = c;
    shell->len += 1;
}

void terminal_remove(int nb)
{
    CURRENT_READLINE_BUFFER

    memmove(
        &shell->buffer[readline_buffer->caret_position - nb],
        &shell->buffer[readline_buffer->caret_position],
        shell->len - readline_buffer->caret_position + 1
    );
    terminal_move_left(nb);
    shell->len -= nb;
}