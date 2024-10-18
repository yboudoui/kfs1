#include "terminal.h"

void terminal_frame_put_entry_at(t_vga_frame* frame, t_vga_entry entry, t_terminal_position position) 
{
	const size_t index = position.row * frame->width + position.column;
	frame->buffer[index] = entry;
}

t_terminal_frame* current_terminal_frame(t_terminal_frame* frame)
{
	static t_terminal_frame* current_frame;
	if (frame != NULL) {
		current_frame = frame;
	}
	return current_frame;
}

void terminal_clear(void)
{
	t_terminal_frame* terminal_frame = current_terminal_frame(NULL);
	t_vga_entry clear_entry = vga_entry(' ', terminal_frame->default_color);

	for (size_t y = 0; y < terminal_frame->frame.height ; y++) {
		for (size_t x = 0; x < terminal_frame->frame.width; x++) {
			const size_t index = y * terminal_frame->frame.width + x;
			terminal_frame->frame.buffer[index] = clear_entry;

		}
	}
}

void terminal_putchar(char c) 
{
	t_terminal_frame* terminal_frame = current_terminal_frame(NULL);
	t_vga_entry entry = vga_entry(c, terminal_frame->default_color);

	terminal_frame_put_entry_at(
		&terminal_frame->frame,
		entry,
		terminal_frame->current_position
	);
	if (++terminal_frame->current_position.column == terminal_frame->frame.width) {
		terminal_frame->current_position.column = 0;
		if (++terminal_frame->current_position.row == terminal_frame->frame.height)
			terminal_frame->current_position.row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
		terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}

void terminal_update_frame(t_terminal_frame frame)
{
	vga_main_frame_update(frame.frame);
}