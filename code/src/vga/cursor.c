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

// Sets the cursor position to (row, col) in the VGA text buffer
void    vga_set_cursor_position(t_vec2 position)
{
    position.x %= VGA_WIDTH;
    position.y %= VGA_HEIGHT;


    // Calculate the linear index in the VGA buffer
    uint16_t linear_position = position.y * VGA_WIDTH + position.x;

    // Send the high byte of the cursor position to VGA port 0x3D4 (index 0x0E)
    outb(VGA_COMMAND_PORT, 0x0E);
    outb(VGA_DATA_PORT, (linear_position >> 8) & 0xFF);  // High byte

    // Send the low byte of the cursor position to VGA port 0x3D4 (index 0x0F)
    outb(VGA_COMMAND_PORT, 0x0F);
    outb(VGA_DATA_PORT, linear_position & 0xFF);  // Low byte
}

t_vec2  get_cursor_position(void)
{
    t_vec2 position;
    uint16_t pos = 0;

    outb(VGA_COMMAND_PORT, 0x0F);
    pos |= inb(VGA_DATA_PORT);
    outb(VGA_COMMAND_PORT, 0x0E);
    pos |= ((uint16_t)inb(VGA_DATA_PORT)) << 8;

    position.y = pos / VGA_WIDTH;
    position.x = pos % VGA_WIDTH;
    return position;
}



DECLARE_BUFFER_INSERT(t_vga_entry)
DECLARE_BUFFER_REMOVE(t_vga_entry)

void vga_frame_update_caret(void)
{
    CURRENT_VGA_FRAME
    vga_frame->caret = vga_frame->cursor.y * VGA_WIDTH + vga_frame->cursor.x;
}

void vga_frame_move_cursor_position_by(int n)
{
    CURRENT_VGA_FRAME

    size_t position = vga_frame->cursor.x + n;

    if (position < 0)
        position = 0;
    if (position > VGA_WIDTH)
        position = VGA_WIDTH;
    vga_frame->cursor.x = position;
    vga_frame_update_caret();
}

void vga_frame_remove(int nb, t_vga_entry default_entry)
{
    CURRENT_VGA_FRAME

	t_buffer vga = {
		.data		= vga_frame->buffer,
		.len		= VGA_MAX_PRINTABLE_CHARACTER,
	};

    m_buffer_remove(t_vga_entry)(
        &vga,
        window_from_position(vga_frame->cursor.x, nb),
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

    m_buffer_insert_one(t_vga_entry)(&vga, vga_frame->caret, entry);
}

bool vga_frame_next_line(void)
{
    CURRENT_VGA_FRAME
    if (vga_frame->cursor.y < VGA_HEIGHT - 1)
    {
        vga_frame->cursor.x = 0;
        vga_frame->cursor.y += 1;
        vga_frame_update_caret();
        return true;
    }
    return false;
}

bool vga_frame_move_cursor_up(void)
{
    CURRENT_VGA_FRAME
    if (vga_frame->cursor.y > 0)
    {
        vga_frame->cursor.y -= 1;
        vga_frame_update_caret();
        return true;
    }
    return false;
}
bool vga_frame_move_cursor_down(void)
{
    CURRENT_VGA_FRAME
    if (vga_frame->cursor.y < VGA_HEIGHT - 1)
    {
        vga_frame->cursor.y += 1;
        vga_frame_update_caret();
        return true;
    }
    return false;
}