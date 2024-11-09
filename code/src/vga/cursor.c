#include "vga.h"
#include "hardware_io.h"
#include "buffer.h"

void    vga_disable_cursor(void)
{
	outb(VGA_COMMAND_PORT, 0x0A);
	outb(VGA_DATA_PORT, 0x20);
}

void    vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(VGA_COMMAND_PORT, 0x0A);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xC0) | cursor_start);

	outb(VGA_COMMAND_PORT, 0x0B);
	outb(VGA_DATA_PORT, (inb(VGA_DATA_PORT) & 0xE0) | cursor_end);
}

DECLARE_BUFFER_INSERT(t_vga_entry)
DECLARE_BUFFER_REMOVE(t_vga_entry)

void vga_frame_move_cursor_position_by(int n)
{
    CURRENT_VGA_FRAME
    clamped_vec2_set_with_linear_position_by(&vga_frame->cursor, n);
}

void vga_frame_remove(int nb, t_vga_entry default_entry)
{
    CURRENT_VGA_FRAME

	t_buffer vga = {
		.data		= vga_frame->buffer,
		.len		= VGA_MAX_PRINTABLE_CHARACTER,
	};
    size_t caret = clamped_vec2_get_linear_position(vga_frame->cursor);

    m_buffer_remove(t_vga_entry)(
        &vga,
        window_from_position(caret, nb),
        (t_buffer){1, 0, &default_entry}
    );
}

void vga_frame_put_entry(t_vga_entry entry)
{
    CURRENT_VGA_FRAME

	t_buffer vga = {
		.data		= vga_frame->buffer,
		.len		= VGA_MAX_PRINTABLE_CHARACTER,
	};
    size_t caret = clamped_vec2_get_linear_position(vga_frame->cursor);
    m_buffer_insert_one(t_vga_entry)(&vga, caret, entry);
}

bool vga_frame_next_line(void)
{
    CURRENT_VGA_FRAME
    return with_clamped_vec2(&vga_frame->cursor, new_line);
}
bool vga_frame_move_cursor_up(void)
{
    CURRENT_VGA_FRAME
    return with_clamped_vec2(&vga_frame->cursor, vec2_up);
}
bool vga_frame_move_cursor_down(void)
{
    CURRENT_VGA_FRAME
    return with_clamped_vec2(&vga_frame->cursor, vec2_down);
}