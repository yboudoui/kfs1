#include "terminal.h"
#include "utils.h"

void terminal_putchar_at(t_vec2 position, char c)
{
	CURRENT_TERMINAL

	t_vga_entry entry = vga_entry(c, terminal->default_color);
	vga_frame_put_entry_at(entry, position);
}

void terminal_putchar(char c)
{
	CURRENT_TERMINAL

	t_vec2 position = {
		.x = terminal->caret_position % VGA_WIDTH,
		.y = terminal->caret_position / VGA_WIDTH,
	};

	terminal_putchar_at(position, c);
	
}

int terminal_write(const char* data, size_t size)
{
	CURRENT_TERMINAL
	for (size_t i = 0; i <= size; i++)
	{
		terminal_putchar(data[i]);
		terminal->caret_position += 1;
	}

	return (size);
}

void	terminal_put_block_at(size_t size, char* buffer, t_vec2 position)
{
	t_vec2 tmp = {0};

	for (size_t index = 0; index < size; index++)
	{
		if(buffer[index] == '\n')
		{
			tmp.x = 0;
			tmp.y += 1;
			continue;
		}

		terminal_putchar_at(vec2_add(position, tmp), buffer[index]);	
		tmp.x += 1;
	}
}