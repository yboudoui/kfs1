#include "readline.h"
#include "ecma48.h"
#include "std_io.h"
#include "terminal.h"

t_readline_buffer* current_readline_buffer(t_readline_buffer* readline_buffer)
{
	static t_readline_buffer* current_readline_buffer = NULL;

	if (readline_buffer != NULL) {
		current_readline_buffer = readline_buffer;
        current_readline_buffer->buffer.len = READLINE_BUFFER_SIZE;
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
    if (new_position > readline_buffer->buffer.len)
        new_position = readline_buffer->buffer.len;

    readline_buffer->caret_position = new_position;
    return (old_position - new_position);
}

DECLARE_BUFFER_INSERT(char)
DECLARE_BUFFER_REMOVE(char)

void    readline_buffer_reset(t_readline_buffer* readline_buffer)
{
	memset(t_readline_buffer)(readline_buffer, (t_readline_buffer){0}, 1);
}

int fd = STD_OUT;

static void on_backspace(char c)
{
    CURRENT_READLINE_BUFFER
    if (readline_buffer->caret_position <= 0) return;

    m_buffer_remove(char)(
        &readline_buffer->buffer,
        window_from_position(readline_buffer->caret_position, -1),
        (t_buffer){1, " "}
    );
    readline_update_caret_position(-1);
    dprintf(fd, "%c", c);
}

static void on_delete(char c)
{
    CURRENT_READLINE_BUFFER
    if (readline_buffer->caret_position <= 0) return;

    m_buffer_remove(char)(
        &readline_buffer->buffer,
        window_from_position(readline_buffer->caret_position, 1),
        (t_buffer){1, " "}
    );
    dprintf(fd, "%c", c);
}

static void on_default(char c)
{
    CURRENT_READLINE_BUFFER

    m_buffer_insert_one(char)(&readline_buffer->buffer, readline_buffer->caret_position, c);
    readline_update_caret_position(+1);
    dprintf(fd, "%c", c);

}

static void on_cursor_mouvement(t_vec2 mouvement)
{
    if(readline_update_caret_position(mouvement.x))
        ecma48_move_cursor(fd, mouvement.x, 0);
}

static t_ecma48_handlers handlers = {
    .on_cursor_mouvement = on_cursor_mouvement,
    .default_char_handler = on_default,
    .char_handlers = {
        ['\b']      = on_backspace,
        ['\177']    = on_delete, 
    }
};

void readline(void)
{
    char                read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t              read_size = read(STD_IN, read_buffer, STD_IO_BUFFER_SIZE);
    for (size_t i = 0; i < read_size; i += ecma48_hooks(&read_buffer[i], &handlers));
}
