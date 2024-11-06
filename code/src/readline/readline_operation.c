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

void on_character(t_ecma48_sequence* data, char* buffer)
{
    CURRENT_READLINE_BUFFER
    if (data->is_controle) return;

    char c = data->character;
    switch (c)
    {
    case '\b':
        if (readline_buffer->buffer[readline_buffer->caret_position - 1] == '\t')
            sprintf(buffer, "\b\b\b\b");
        else
            sprintf(buffer, "\b");
        readline_remove(1);
        break;
    case '\177':
        if (readline_update_caret_position(+1))
            readline_remove(1);
        break;
    case '\t':
        readline_insert(c);
        ecma48_move_cursor(buffer, +TABSIZE, 0);
        // sprintf(buffer, "PPPP");
        break;
    default:
        readline_insert(data->character);
        buffer[0] = c;
        ecma48_move_cursor(&buffer[1], +1, 0);
        break;
    }
}

void on_cursor_mouvement(t_ecma48_sequence* data, char * buffer)
{
    if (data->is_controle == false) return ;
    t_vec2 vec = data->cursor_movement;

    if(readline_update_caret_position(vec.x))
        ecma48_move_cursor(buffer, vec.x, 0);
}

void readline(void)
{
    CURRENT_READLINE_BUFFER

    t_ecma48_sequence   current_sequence = {0};
    char                read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t              read_size = read(STD_IN, read_buffer, STD_IO_BUFFER_SIZE);

    char tmp[64] = {0};
    for (size_t i = 0; i < read_size; i++)
    {
        i += ecma48_parse_sequence(&read_buffer[i], &current_sequence);
        on_character(&current_sequence, tmp);

        on_cursor_mouvement(&current_sequence, tmp);
        dprintf(STD_OUT, "%s", tmp);
        // if (readline_buffer->cursor_movement)
            // ecma48_move_cursor(tmp, readline_buffer->cursor_movement, 0);
    }
}
