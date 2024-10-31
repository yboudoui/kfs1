#include "readline.h"

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer)
{
	static t_readline_buffer* current_readline_buffer = NULL;

	if (readline_buffer != NULL) {
		current_readline_buffer = readline_buffer;
	}
	return current_readline_buffer;
};

int readline_update_caret_position(int n)
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

int readline_is_character(char c, int position_relatif)
{
    CURRENT_READLINE_BUFFER

    char*   buffer      = readline_buffer->buffer;
    size_t  position    = readline_buffer->caret_position + position_relatif;

    return (buffer[position] == c);
}

void readline_insert(char c)
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

void readline_remove(size_t nb)
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

#include "keyboard.h"
#define TABSIZE 4
int readline_keyboard_handler(t_key_scancode key_scancode)
{
    char    character = codepage_437[key_scancode];
    int     move_by = (character == '\t') ? TABSIZE : 1;

    switch (key_scancode)
    {
        case KEY_BACKSPACE:
            readline_remove(1);
            vga_frame_move_cursor_position_by(-move_by);
            break;
        case KEY_DELETE:
            if (readline_update_caret_position(+1))
                readline_remove(1);
            break;
        case KEY_LEFT:
            if (readline_update_caret_position(-1))
                vga_frame_move_cursor_position_by(-move_by);
            break;
        case KEY_RIGHT:
            if (readline_update_caret_position(+1))
                vga_frame_move_cursor_position_by(move_by);
            break;
        default:
            readline_insert(character);
            vga_frame_move_cursor_position_by(move_by);
            break;
    }
    return 0;
}