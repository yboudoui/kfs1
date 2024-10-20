#include "vga.h"
#include "utils.h"

void vga_frame_put_entry_at(t_vga_frame* vga_frame, t_vga_entry entry, t_vec2 position) 
{
	size_t        index;

	index = position.y * VGA_WIDTH + position.x;
	vga_frame->buffer[index] = entry;
}

void vga_fill(t_vga_frame* vga_frame, t_vga_entry entry)
{
	memset(t_vga_entry)(vga_frame->buffer, entry,  VGA_MAX_PRINTABLE_CHARACTER);
}

void vga_main_frame_update(t_vga_frame vga_frame)
{
	vga_set_cursor_position(vga_frame.cursor);
	memcpy(VIDEO_MEMORY, vga_frame.buffer, sizeof(t_vga_entry) * VGA_MAX_PRINTABLE_CHARACTER);
}