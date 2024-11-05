#include "readline.h"
#include "ecma48.h"
#include "std_io.h"
#include "terminal.h"

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer)
{
	static t_readline_buffer* current_readline_buffer = NULL;

	if (readline_buffer != NULL) {
		current_readline_buffer = readline_buffer;
	}
	return current_readline_buffer;
};

void    readline_move_cursor(int n)
{
    CURRENT_READLINE_BUFFER

    int sign = 1;
    if (n < 0) {
        sign = -1;
        n *= -1;
    }

    int pos = readline_buffer->caret_position;

    // TODO: check limit

    for (size_t i = 0; i < n; i++)
    {
        char c = readline_buffer->buffer[pos + (sign * i)];
        int dir = (c == '\t') ? TABSIZE : 1;
        dir *= sign;
        readline_buffer->cursor_movement += dir;
    }
}

int     readline_update_caret_position(int n)
{
    CURRENT_READLINE_BUFFER

    int  old_position   = readline_buffer->caret_position;
    int  new_position   = old_position + n;

    if (new_position < 0)
        new_position = 0;
    if (new_position > READLINE_BUFFER_SIZE)
        new_position = READLINE_BUFFER_SIZE;

    readline_buffer->caret_position = new_position;
    return (old_position - new_position);
}

void    readline_insert(char c)
{
    CURRENT_READLINE_BUFFER

    char*   buffer      = readline_buffer->buffer;
    size_t  position    = readline_buffer->caret_position;

    memmove(
        &buffer[position + 1],
        &buffer[position],
        readline_buffer->size - position + 1
    );

    buffer[position] = c;
    readline_update_caret_position(+1);
    readline_buffer->size += 1;
}

void    readline_remove(int nb)
{
    CURRENT_READLINE_BUFFER

    char*   buffer      = readline_buffer->buffer;
    size_t  position    = readline_buffer->caret_position;

    memmove(
        &buffer[position - nb],
        &buffer[position],
        readline_buffer->size - position + 1
    );
    readline_update_caret_position(-nb);
    readline_buffer->size -= nb;
}

void    readline_buffer_reset(t_readline_buffer* readline_buffer)
{
	memset(t_readline_buffer)(readline_buffer, (t_readline_buffer){0}, 1);
}

void on_character(t_ecma48_sequence* data)
{
    if (data->is_controle) return;
    switch (data->character)
    {
    case '\b':
        readline_remove(1);
        readline_move_cursor(-1);
        break;
    case '\177':
        if (readline_update_caret_position(+1))
            readline_remove(1);
        break;
    default:
        readline_insert(data->character);
        readline_move_cursor(+1);
        break;
    }
}

void on_cursor_mouvement(t_ecma48_sequence* data)
{
    if (data->is_controle == false) return ;
    t_vec2 vec = data->cursor_movement;

    if(readline_update_caret_position(vec.x))
        readline_move_cursor(vec.x);
}

void readline(void)
{
    CURRENT_READLINE_BUFFER
    readline_buffer->cursor_movement = 0;

    t_ecma48_sequence   current_sequence = {0};
    char                read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t              read_size = read(STD_IN, read_buffer, STD_IO_BUFFER_SIZE);

    for (size_t i = 0; i < read_size; i++)
    {
        i += ecma48_parse_sequence(&read_buffer[i], &current_sequence);
        on_character(&current_sequence);
        on_cursor_mouvement(&current_sequence);
    }
    char tmp[64] = {0};
    if (readline_buffer->cursor_movement)
        ecma48_move_cursor(tmp, readline_buffer->cursor_movement, 0);
    dprintf(STD_OUT, "%s%s", readline_buffer->buffer, tmp);
}