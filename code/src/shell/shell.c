#include "shell.h"

int shell_get_character(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    terminal_handle_input(key_scancode);
     
    terminal_reset_position();
    terminal_clear();
    terminal_write(shell->buffer, shell->len);
    terminal_update();
    return 0;
}