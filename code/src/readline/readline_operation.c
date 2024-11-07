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

int     readline_update_caret_position(int n)
{
    CURRENT_READLINE_BUFFER

    int  old_position   = readline_buffer->caret_position;
    int  new_position   = old_position + n;

    if (new_position < 0)
        new_position = 0;
    if (new_position > readline_buffer->size)
        new_position = readline_buffer->size;

    readline_buffer->caret_position = new_position;
    return (old_position - new_position);
}

DECLARE_MEMMOVE(char)

void    readline_insert(char c)
{
    CURRENT_READLINE_BUFFER

    char*   buffer      = readline_buffer->buffer;
    size_t  position    = readline_buffer->caret_position;

    memmove(char)(
        &buffer[position + 1],
        &buffer[position],
        readline_buffer->size - position + 1
    );

    buffer[position] = c;
    readline_buffer->size += 1;
    readline_update_caret_position(+1);
}

void    readline_remove(int nb)
{
    CURRENT_READLINE_BUFFER

    if (readline_buffer->caret_position <= 0) return;
    char*   buffer      = readline_buffer->buffer;
    size_t  position    = readline_buffer->caret_position;

    memmove(char)(
        &buffer[position - nb],
        &buffer[position],
        readline_buffer->size - position + 1
    );
    readline_buffer->size -= nb;
    readline_update_caret_position(-nb);
}

void    readline_buffer_reset(t_readline_buffer* readline_buffer)
{
	memset(t_readline_buffer)(readline_buffer, (t_readline_buffer){0}, 1);
}


// void on_backspace(int fd, char c)
// {
//     readline_remove(1);
//     dprintf(fd, "%c", '\b');
// }

// void on_delete(int fd, char c)
// {
//     if (readline_update_caret_position(+1)){
//         readline_remove(1);
//         dprintf(fd, "%c", '\177');
//     }
// }

// void on_default(int fd, char c)
// {
//     readline_insert(c);
//     dprintf(fd, "%c", c);
// }

void on_character(int fd, t_ecma48_sequence* data)
{
    if (data->is_controle) {
        t_vec2 vec = data->cursor_movement;

        if(readline_update_caret_position(vec.x))
            ecma48_move_cursor(fd, vec.x, 0);
        return;
    };

    switch (data->character)
    {
        case '\b':
            readline_remove(1);
            dprintf(fd, "%c", '\b');
            break;
        case '\177':
            if (readline_update_caret_position(+1)){
                readline_remove(1);
                dprintf(fd, "%c", '\177');
            }
            break;
        default:
            readline_insert(data->character);
            dprintf(fd, "%c", data->character);
            break;
    }
}

void readline(void)
{
    t_ecma48_sequence   current_sequence = {0};
    char                read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t              read_size = read(STD_IN, read_buffer, STD_IO_BUFFER_SIZE);

    for (size_t i = 0; i < read_size; i++)
    {
        i += ecma48_parse_sequence(&read_buffer[i], &current_sequence);
        on_character(STD_OUT, &current_sequence);
    }
}
