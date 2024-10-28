#include "terminal.h"
#include "utils.h"

void terminal_putchar_at(t_vec2 position, char c) 
{
	CURRENT_TERMINAL //bootloader fait trop tot, current terminal pas initialise, j'ai mis ca en dur ici pour que ce soit beau, probleme a remonter

	//printf("Terminal bg:%d\nTerminal fg:%d", terminal->default_color.bg, terminal->default_color.fg); //marche pas ni en %x ni en %d
	if (!terminal->default_color.bg){
		vga_frame_put_entry_at(
			&terminal->vga_frame,
			vga_entry(c, terminal->default_color),
			position
		);
	}
	else
	{
		vga_frame_put_entry_at(
			&terminal->vga_frame,
			vga_entry(c, (t_vga_entry_color){.bg=VGA_COLOR_BLACK,.fg=VGA_COLOR_RED}),
			position
		);
	}
}

void terminal_putchar(char c) 
{
	CURRENT_TERMINAL
	
	if (c == '\t') {
		for (size_t i = 1; i < TABSIZE; i++) {
			terminal_putchar_at(terminal->current_position, ' ');
			terminal->current_position.x += 1;
    	}
	} else if (c == '\n') {
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
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
	return (size);
}

void terminal_put_block_at(char* buffer, t_vec2 position)
{
	t_vec2 tmp = {};

	for (size_t index = 0; buffer[index]; index++)
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