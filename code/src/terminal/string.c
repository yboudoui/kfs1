#include "terminal.h"
#include "utils.h"

void terminal_return(t_terminal* terminal)
{
	terminal->current_position.x = 0;
	terminal->current_position.y += 1;
}

void terminal_putchar_at(t_terminal* terminal, t_vec2 position, char c) 
{
	t_vga_entry_color	color;
	t_vga_entry			entry;
	t_vga_frame*		vga_frame;

	color = terminal->default_color;
	entry = vga_entry(c, color);
	vga_frame = &terminal->vga_frame;
	vga_frame_put_entry_at(vga_frame, entry, position);
}

void terminal_loop_overflow(t_terminal* terminal)
{
	if (terminal->current_position.x >= VGA_WIDTH)
		terminal->current_position.x = 0;
	if (terminal->current_position.y >= VGA_HEIGHT)
		terminal->current_position.y = 0;
}

void terminal_putchar(t_terminal* terminal, char c) 
{
	terminal_loop_overflow(terminal);
	
	if (c == '\n') {
        terminal_return(terminal);
		return ;
	} 
	terminal_putchar_at(terminal, terminal->current_position, c);

	if (++terminal->current_position.x == VGA_WIDTH) {
		terminal->current_position.x = 0;
		if (++terminal->current_position.y == VGA_HEIGHT)
			terminal->current_position.y = 0;
	}
}

void terminal_write(t_terminal* terminal, const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(terminal, data[i]);
}

void terminal_write_string(t_terminal* terminal, const char* data) 
{
	terminal_write(terminal, data, strlen(data));
}

void terminal_write_number(t_terminal* terminal, t_itoa_base base, int nb)
{
    char buffer[64] = {0};

	itoa_base(base, buffer, nb);
	terminal_write(terminal, buffer, strlen(buffer));
}