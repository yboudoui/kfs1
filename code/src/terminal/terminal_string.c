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
	
	// if (c == '\t') {
	// 	for (size_t i = 1; i < TABSIZE; i++) {
	// 		terminal_putchar_at(terminal->current_position, ' ');
	// 		terminal->current_position.x += 1;
    // 	}
	// } else
	if (c == '\n') {
		terminal->current_position.x = 0;
		terminal->current_position.y += 1;
		return ;
	} else {
		terminal_putchar_at(terminal->current_position, c);
	}

	if (++terminal->current_position.x == VGA_WIDTH) {
		terminal->current_position.x = 0;
		if (++terminal->current_position.y == VGA_HEIGHT)
			terminal->current_position.y = 0;
	}
}

int terminal_write(const char* data, size_t size)
{
	CURRENT_TERMINAL

	t_ecma48_sequence 	seq = {0};

	for (size_t i = 0; i < size; i++)
	{
		i += parse_sequence(&data[i], &seq);
		if (seq.type == CHARACTER) 
		{
			terminal_putchar_at(terminal->current_position, seq.data.character);
			terminal->current_position.x += 1;
		}
		else if (seq.type == CURSOR_MOVEMENT) {
			printk("[%d]", seq.data.cursor_movement.x);
			vga_frame_move_cursor_position_by(seq.data.cursor_movement.x);
			terminal->current_position.x += seq.data.cursor_movement.x;
			printk("[%d] + > %d", seq.data.cursor_movement.x, terminal->current_position.x);
		}
	}
	return (size);
}

void	terminal_update(void)
{
	char	read_buffer[STD_IO_BUFFER_SIZE] = {0};
    size_t	read_size;

	read_size = read(STD_OUT, read_buffer, STD_IO_BUFFER_SIZE);

	terminal_write(read_buffer, read_size);
	vga_main_frame_update();
}

void terminal_put_block_at(size_t size, char* buffer, t_vec2 position)
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