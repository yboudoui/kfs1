#include "terminal.h"

t_terminal* terminal_current(t_terminal* terminal)
{
	static t_terminal* current_terminal = NULL;

	if (terminal != NULL) {
		current_terminal = terminal;
        size_t working_buffer = current_terminal->readline.current_working_buffer;
	    current_readline_buffer(&current_terminal->readline.readline_buffer[working_buffer]);
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

bool move_cursor_to_new_line_at(int n)
{
    CURRENT_TERMINAL

    if (move_cursor_down())
    {
        terminal->vga_frame.cursor.x = n;
        return true;
    }
    return false;
}