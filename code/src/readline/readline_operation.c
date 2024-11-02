#include "readline.h"
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

void     readline_update(void)
{
    char buffer[STD_IO_BUFFER_SIZE] = {0};

    t_key_scancode key_scancode;
    size_t read_size = read(STDOUT, buffer, STD_IO_BUFFER_SIZE);

    char character;
    int move_by;

    while (get_scancode_from_sequence(&read_size, (char**)&buffer, &key_scancode))
    {
        switch (key_scancode)
        {
            case KEY_BACKSPACE:
                readline_remove(1);
                move_cursor(-1);
                break;
            case KEY_DELETE:
                if (readline_update_caret_position(+1))
                    readline_remove(1);
                break;
            case KEY_LEFT:
                if (readline_update_caret_position(-1))
                    move_cursor(-1);
                break;
            case KEY_RIGHT:
                if (readline_update_caret_position(+1))
                    move_cursor(+1);
                break;
            default:
                character = codepage_437[key_scancode];
                readline_insert(character);
                move_by = (character == '\t')? TABSIZE : 1;
                move_cursor(move_by);
                break;
        }
    }

}