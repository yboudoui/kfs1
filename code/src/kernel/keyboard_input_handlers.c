#include "keyboard_input_handlers.h"
#include "codepage_437.h"

#include "kernel.h"

int terminal_input_fallback(t_key_scancode key_scancode)
{
    int     move_by = +1;
    char    character = codepage_437[key_scancode];

    readline_insert(character);
    if (character == '\t')
        move_by = +TABSIZE;

    move_cursor_position_by(move_by);
    return 0;
}

int terminal_input_on_return(t_key_scancode key_scancode)
{
    CURRENT_TERMINAL
    readline_insert(codepage_437[key_scancode]);

    terminal->readline.current_working_buffer += 1;
    terminal->readline.current_working_buffer %= TERMINAL_READLINE_BUFFER_SIZE;

    size_t working_buffer = terminal->readline.current_working_buffer;

    readline_buffer_reset(&terminal->readline.readline_buffer[working_buffer]);
    current_readline_buffer(&terminal->readline.readline_buffer[working_buffer]);

    if (!move_cursor_down())
        shell_scroll_down();
    terminal->vga_frame.cursor.x = 0;
    return 0;
}

int terminal_input_on_backspace(t_key_scancode key_scancode)
{
    if (readline_is_character('\n', -1))
        return 0;

    int move_by = -1;

    if (readline_is_character('\t', -1))
        move_by = -TABSIZE;

    readline_remove(1);
    move_cursor_position_by(move_by);
    return 0;
}

int terminal_input_on_del(t_key_scancode key_scancode)
{
    if (readline_update_caret_position(+1))
        readline_remove(1);
    return 0;
}

int terminal_input_on_button_left(t_key_scancode key_scancode)
{
    int move_by = -1;

    if (readline_is_character('\t', -1))
        move_by = -TABSIZE;

    if (readline_update_caret_position(-1))
        move_cursor_position_by(move_by);
    return 0;
}

int terminal_input_on_button_right(t_key_scancode key_scancode)
{
    int move_by = +1;

    if (readline_is_character('\t', 0))
        move_by = +TABSIZE;

    if (readline_update_caret_position(+1))
        move_cursor_position_by(move_by);
    return 0;
}

int terminal_input_on_button_up(t_key_scancode key_scancode)
{
    if (!move_cursor_up())
        shell_scroll_up();
    return 0;
}

int terminal_input_on_button_down(t_key_scancode key_scancode)
{
    if (!move_cursor_down())
        shell_scroll_down();
    return 0;
}
