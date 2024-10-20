#include "terminal.h"

t_terminal* terminal_current(t_terminal* terminal_frame)
{
	static t_terminal* current_terminal_frame = NULL;

	if (terminal_frame != NULL) {
		current_terminal_frame = terminal_frame;
	}
	return current_terminal_frame;
}

void terminal_clear(t_terminal* terminal)
{
	t_vga_entry_color	color;
	t_vga_entry			clear_entry;
	t_vga_frame*		vga_frame;
	
	color = terminal->default_color;
	clear_entry = vga_entry(' ', color);
	vga_frame = &terminal->vga_frame;

	vga_fill(vga_frame, clear_entry);
}

void terminal_reset_position(void)
{
	t_terminal* terminal_frame;

	terminal_frame = terminal_current(NULL);
	terminal_frame->current_position = (t_vec2){0};
}
