#include "terminal.h"

t_terminal* current_terminal(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		current_terminal = terminal;
	}
	return current_terminal;
}

void move_cursor_position_by(int n)
{
    CURRENT_TERMINAL

    size_t position = terminal->vga_frame.cursor.x + n;

    if (position < 0)
        position = 0;
    if (position > VGA_WIDTH)
        position = VGA_WIDTH;
    terminal->vga_frame.cursor.x = position;
}

bool move_cursor_up(void)
{
    CURRENT_TERMINAL
    if (terminal->vga_frame.cursor.y > 0)
    {
        terminal->vga_frame.cursor.y -= 1;
        return true;
    }
    return false;
}

bool move_cursor_down(void)
{
    CURRENT_TERMINAL
    if (terminal->vga_frame.cursor.y < VGA_HEIGHT - 1)
    {
        terminal->vga_frame.cursor.y += 1;
        return true;
    }
    return false;
}