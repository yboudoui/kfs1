#include "vga.h"
#include "utils.h"
#include "hardware_io.h"


t_vga_frame* current_vga_frame(t_vga_frame* vga_frame)
{
	static t_vga_frame* current_vga_frame = NULL;

	if (vga_frame != NULL) {
		current_vga_frame = vga_frame;
	}
	return current_vga_frame;
}

void	vga_frame_init(t_vga_frame* vga_frame)
{
	vga_frame->cursor.max = (t_vec2){.x = VGA_WIDTH, .y = VGA_HEIGHT};
	vga_frame->cursor.min = (t_vec2){.x = 0, .y = 0};
}

void vga_frame_put_entry_at(t_vga_entry entry, t_vec2 position) 
{
	CURRENT_VGA_FRAME

	position.x %= VGA_WIDTH;
	position.y %= VGA_HEIGHT;
	size_t index = position.y * VGA_WIDTH + position.x;
	vga_frame->buffer[index] = entry;
}

void vga_fill(t_vga_entry entry)
{
	CURRENT_VGA_FRAME

	memset(t_vga_entry)(vga_frame->buffer, entry,  VGA_MAX_PRINTABLE_CHARACTER);
}

// Sets the cursor position to (row, col) in the VGA text buffer
static void    vga_set_cursor_position(void)
{
    CURRENT_VGA_FRAME

    size_t caret = clamped_vec2_get_linear_position(vga_frame->cursor);

    // Send the high byte of the cursor position to VGA port 0x3D4 (index 0x0E)
    outb(VGA_COMMAND_PORT, 0x0E);
    outb(VGA_DATA_PORT, (caret >> 8) & 0xFF);  // High byte

    // Send the low byte of the cursor position to VGA port 0x3D4 (index 0x0F)
    outb(VGA_COMMAND_PORT, 0x0F);
    outb(VGA_DATA_PORT, caret & 0xFF);  // Low byte
}

void vga_main_frame_update(void)
{
	CURRENT_VGA_FRAME
	vga_set_cursor_position();
	memcpy(VIDEO_MEMORY, vga_frame->buffer, sizeof(t_vga_entry) * VGA_MAX_PRINTABLE_CHARACTER);
}