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
    readline_insert(codepage_437[key_scancode]);

    CURRENT_TERMINAL

    int n = get_char_occurences(terminal->readline_buffer.buffer, '\n');
    if (n >= VGA_HEIGHT) {
        *((int*)terminal->user_data) +=1;
        terminal->vga_frame.cursor.x = 0;
    }
    else
        move_cursor_to_new_line_at(0);
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
    CURRENT_TERMINAL

    // terminal->vga_frame.cursor.y -= 1;
    if(*((int*)terminal->user_data)>0)
        *((int*)terminal->user_data) -= 1;
    return 0;
}

int terminal_input_on_button_down(t_key_scancode key_scancode)
{
    CURRENT_TERMINAL


    int n = get_char_occurences(terminal->readline_buffer.buffer, '\n');

//    terminal->vga_frame.cursor.y += 1;
    if(*((int*)terminal->user_data) + 23 < n )
        *((int*)terminal->user_data) += 1;
    return 0;
}
