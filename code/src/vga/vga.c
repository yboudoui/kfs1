#include "vga.h"
#include "utils.h"

t_vga_frame* current_vga_frame(t_vga_frame* vga_frame)
{
	static t_vga_frame* current_vga_frame = NULL;

	if (vga_frame != NULL) {
		current_vga_frame = vga_frame;
	}
	return current_vga_frame;
}

void vga_frame_put_entry_at(t_vga_entry entry, t_vec2 position) 
{
	CURRENT_VGA_FRAME
	size_t index = position.y * VGA_WIDTH + position.x;
	vga_frame->buffer[index] = entry;
}

void vga_fill(t_vga_entry entry)
{
	CURRENT_VGA_FRAME
	memset(t_vga_entry)(vga_frame->buffer, entry,  VGA_MAX_PRINTABLE_CHARACTER);
}

void vga_main_frame_update(void)
{
	CURRENT_VGA_FRAME
	vga_set_cursor_position(vga_frame->cursor);
	memcpy(VIDEO_MEMORY, vga_frame->buffer, sizeof(t_vga_entry) * VGA_MAX_PRINTABLE_CHARACTER);
}