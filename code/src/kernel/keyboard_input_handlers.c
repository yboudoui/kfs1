#include "keyboard_input_handlers.h"


int terminal_move_left(int n)
{
    CURRENT_SHELL

    size_t old = shell->pos;
    if (shell->pos > 0)
        shell->pos -= n;
    else
        shell->pos = 0;
    return (old - shell->pos);
}

int terminal_move_right(int n)
{
    CURRENT_SHELL

    size_t old = shell->pos;
    if (shell->pos < shell->len)
        shell->pos += n;
    else
        shell->pos = shell->len;
    return (old - shell->pos);
}

void terminal_insert(char c)
{
    CURRENT_SHELL

    memmove(
        &shell->buffer[shell->pos + 1],
        &shell->buffer[shell->pos],
        shell->len - shell->pos + 1
    );
    shell->buffer[shell->pos++] = c;
    shell->len += 1;
}

void terminal_remove(int nb)
{
    CURRENT_SHELL

    memmove(
        &shell->buffer[shell->pos - nb],
        &shell->buffer[shell->pos],
        shell->len - shell->pos + 1
    );
    terminal_move_left(nb);
    shell->len -= nb;
}




///////

static int terminal_input_fallback(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    terminal_insert(codepage_437[key_scancode]);
    shell->terminal.vga_frame.cursor.x += 1;
    return 0;
}

static int terminal_input_on_return(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    terminal_insert(codepage_437[key_scancode]);
    shell->terminal.vga_frame.cursor.x = 0;
    shell->terminal.vga_frame.cursor.y += 1;
    return 0;
}

static int terminal_input_on_backspace(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    if (shell->buffer[shell->pos] == '\t') {
        terminal_remove(TABSIZE);
        shell->terminal.vga_frame.cursor.x -= TABSIZE;
    }
    else if (shell->buffer[shell->pos] == '\n'){
        shell->terminal.vga_frame.cursor.y -= 1;
        shell->terminal.vga_frame.cursor.x = shell->pos - 1;
    } else {
        terminal_remove(1);
        shell->terminal.vga_frame.cursor.x -= 1;
    }
    return 0;
}

static int terminal_input_on_del(t_key_scancode key_scancode)
{
    CURRENT_SHELL
    size_t to_remove = 1;

    if (shell->buffer[shell->pos] == '\t')
        to_remove = TABSIZE;

    if (shell->pos == shell->len)
        shell->buffer[shell->pos] = 0;
    else {
        memcpy(
            &shell->buffer[shell->pos],
            &shell->buffer[shell->pos + to_remove],
            shell->len - shell->pos
        );
        // shell->terminal.vga_frame.cursor.x -= to_remove;
    }

    return 0;
}

static int terminal_input_on_tab(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    terminal_insert('\t');
    shell->terminal.vga_frame.cursor.x += TABSIZE;
    return 0;
}

static int terminal_input_on_button_left(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    if (terminal_move_left(1))
        shell->terminal.vga_frame.cursor.x -= 1;
    return 0;
}

static int terminal_input_on_button_right(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    if (terminal_move_right(1))
        shell->terminal.vga_frame.cursor.x += 1;
    return 0;
}

static int terminal_input_on_button_up(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    shell->terminal.vga_frame.cursor.y -= 1;
    return 0;
}

static int terminal_input_on_button_down(t_key_scancode key_scancode)
{
    CURRENT_SHELL

    shell->terminal.vga_frame.cursor.y += 1;
    return 0;
}

t_terminal_input_handler    terminal_input_handler(void)
{
    return (t_terminal_input_handler){
        .default_handler = terminal_input_fallback,
        .handlers = {
            [KEY_ENTER]     = terminal_input_on_return,
            [KEY_BACKSPACE] = terminal_input_on_backspace,
            [KEY_TAB]       = terminal_input_on_tab,
            [KEY_DELETE]    = terminal_input_on_del,
            [KEY_LEFT]      = terminal_input_on_button_left,
            [KEY_RIGHT]     = terminal_input_on_button_right,
            [KEY_UP]        = terminal_input_on_button_up,
            [KEY_DOWN]      = terminal_input_on_button_down,
        }
    };
}
