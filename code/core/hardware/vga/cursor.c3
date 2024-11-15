module vga;

import utils::vector;
import hardware;

const ushort    COMMAND_PORT    = 0x3D4;
const ushort    DATA_PORT       = 0x3D5;


fn void    disable_cursor()
{
	hardware::outb(COMMAND_PORT, 0x0A);
	hardware::outb(DATA_PORT, 0x20);
}

// #define VGA_ENABLE_CURSOR   vga_enable_cursor(14, 15);
// TODO reabilit this

fn void    enable_cursor(char cursor_start, char cursor_end)
{
	char data;

	hardware::outb(COMMAND_PORT, 0x0A);
	data = (char)hardware::inb(DATA_PORT);
	hardware::outb(DATA_PORT, (data & 0xC0) | cursor_start);

	hardware::outb(COMMAND_PORT, 0x0B);
	data = (char)hardware::inb(DATA_PORT);
	hardware::outb(DATA_PORT, (data & 0xE0) | cursor_end);
}

fn void set_cursor_position(uint cursor_position)
{
    // Send the high byte of the cursor position to VGA port 0x3D4 (index 0x0E)
    hardware::outb(COMMAND_PORT, 0x0E);
    hardware::outb(DATA_PORT, (char)(cursor_position >> 8) & 0xFF);  // High byte

    // Send the low byte of the cursor position to VGA port 0x3D4 (index 0x0F)
    hardware::outb(COMMAND_PORT, 0x0F);
    hardware::outb(DATA_PORT, (char)(cursor_position & 0xFF));  // Low byte
}