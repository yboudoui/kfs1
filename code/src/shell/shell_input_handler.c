#include "keyboard_input_handlers.h"
#include "shell.h"

int shell_input_on_return(t_key_scancode key_scancode)
{
    readline_insert(codepage_437[key_scancode]);
    shell_next_line();
    return 0;
}

int shell_input_on_button_up(t_key_scancode key_scancode)
{
    if (!move_cursor_up())
        shell_scroll_up();
    return 0;
}

int shell_input_on_button_down(t_key_scancode key_scancode)
{
    if (!move_cursor_down())
        shell_scroll_down();
    return 0;
}
