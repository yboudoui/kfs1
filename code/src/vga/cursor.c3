module vga::cursor;

import vga::constante;
import hardware;

fn void    vga_disable_cursor()
{
	hardware::outb(constante::VGA_COMMAND_PORT, 0x0A);
	hardware::outb(constante::VGA_DATA_PORT, 0x20);
}

// #define VGA_ENABLE_CURSOR   vga_enable_cursor(14, 15);
// TODO reabilit this

fn void    vga_enable_cursor(char cursor_start, char cursor_end)
{
	char data;

	hardware::outb(constante::VGA_COMMAND_PORT, 0x0A);
	data = hardware::inb(constante::VGA_DATA_PORT);
	hardware::outb(constante::VGA_DATA_PORT, (data & 0xC0) | cursor_start);

	hardware::outb(constante::VGA_COMMAND_PORT, 0x0B);
	data = hardware::inb(constante::VGA_DATA_PORT);
	hardware::outb(constante::VGA_DATA_PORT, (data & 0xE0) | cursor_end);
}