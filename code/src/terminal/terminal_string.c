#include "terminal.h"
#include "utils.h"

void terminal_putchar_at(t_vec2 position, char c)
{
	CURRENT_TERMINAL

	t_vga_entry entry = vga_entry(c, terminal->default_color);
	vga_frame_put_entry_at(entry, position);
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