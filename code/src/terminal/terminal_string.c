#include "terminal.h"
#include "utils.h"

void terminal_return(void)
{
	t_terminal*	terminal = terminal_current(NULL);
	
	terminal->current_position.x = 0;
	terminal->current_position.y += 1;
}

void terminal_putchar_at(t_vec2 position, char c) 
{
	t_terminal*	terminal = terminal_current(NULL);

	vga_frame_put_entry_at(
		&terminal->vga_frame,
		vga_entry(c, terminal->default_color),
		position
	);
}

void terminal_loop_overflow(void)
{
	t_terminal*	terminal = terminal_current(NULL);

	if (terminal->current_position.x >= VGA_WIDTH)
		terminal->current_position.x = 0;
	if (terminal->current_position.y >= VGA_HEIGHT)
		terminal->current_position.y = 0;
}

void terminal_putchar(char c) 
{
	t_terminal*	terminal = terminal_current(NULL);
	terminal_loop_overflow();
	
	switch (c) {
		case '\n':
			terminal_return();
			break;
		case '\t':
			for (size_t i = 1; i < TABSIZE; i++) {
				terminal_putchar_at(terminal->current_position, ' ');
				terminal->current_position.x += 1;
    		}
			break;
		default:
			terminal_putchar_at(terminal->current_position, c);
			break;
	}

	if (++terminal->current_position.x == VGA_WIDTH) {
		terminal->current_position.x = 0;
		if (++terminal->current_position.y == VGA_HEIGHT)
			terminal->current_position.y = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_write_string(const char* data) 
{
	terminal_write(data, strlen(data));
}

void terminal_write_number(t_itoa_base base, int nb)
{
    char buffer[64];

	itoa_base(base, buffer, nb);
	terminal_write(buffer, strlen(buffer));
}