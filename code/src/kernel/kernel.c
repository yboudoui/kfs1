#include "utils.h"
#include "shell.h"

int terminal_move_left(int n)
{
    t_shell* shell = current_shell(NULL);

    size_t old = shell->pos;
    if (shell->pos > 0)
        shell->pos -= n;
    else
        shell->pos = 0;
    return (old - shell->pos);
}

int terminal_move_right(int n)
{
    t_shell* shell = current_shell(NULL);

    size_t old = shell->pos;
    if (shell->pos < shell->len)
        shell->pos += n;
    else
        shell->pos = shell->len;
    return (old - shell->pos);
}

void terminal_insert(char c)
{
    t_shell* shell = current_shell(NULL);

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
    t_shell* shell = current_shell(NULL);

    memmove(
        &shell->buffer[shell->pos - nb],
        &shell->buffer[shell->pos],
        shell->len - shell->pos + 1
    );
    terminal_move_left(nb);
    shell->len -= nb;
}


int terminal_input_fallback(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    terminal_insert(codepage_437[key_scancode]);
    shell->terminal.vga_frame.cursor.x += 1;
    return 0;
}

int terminal_input_on_return(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    terminal_insert(codepage_437[key_scancode]);
    shell->terminal.vga_frame.cursor.x = 0;
    shell->terminal.vga_frame.cursor.y += 1;
    return 0;
}

int terminal_input_on_backspace(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);
    size_t to_remove = 1;

    switch (shell->buffer[shell->pos])
    {
        case '\t':
            to_remove = TABSIZE;
            break;
        case '\n':
            shell->terminal.vga_frame.cursor.y -= 1;
            shell->terminal.vga_frame.cursor.x = shell->pos - 1;
            break;
    }
    terminal_remove(to_remove);
    shell->terminal.vga_frame.cursor.x -= to_remove;
    return 0;
}

int terminal_input_on_del(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);
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

int terminal_input_on_tab(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    terminal_insert('\t');
    shell->terminal.vga_frame.cursor.x += TABSIZE;
    return 0;
}

int terminal_input_on_button_left(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    if (terminal_move_left(1))
        shell->terminal.vga_frame.cursor.x -= 1;
    return 0;
}

int terminal_input_on_button_right(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    if (terminal_move_right(1))
        shell->terminal.vga_frame.cursor.x += 1;
    return 0;
}

int terminal_input_on_button_up(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->terminal.vga_frame.cursor.y -= 1;
    return 0;
}

int terminal_input_on_button_down(t_key_scancode key_scancode)
{
    t_shell* shell = current_shell(NULL);

    shell->terminal.vga_frame.cursor.y += 1;
    return 0;
}


void kernel_main(void)
{
	VGA_ENABLE_CURSOR
	t_shell shell = {
        .buffer = {' '},
	    .terminal = (t_terminal){
            .default_color = (t_vga_entry_color){
				.fg = VGA_COLOR_WHITE,
				.bg = VGA_COLOR_BLACK,
			},
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
            },
        },
    };
	current_shell(&shell);
	terminal_clear();
	terminal_update();

	while (keyboard_handler(shell_get_character) == 0);
}