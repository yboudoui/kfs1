#include "vga.h"

void vga_main_frame_update(t_vga_frame frame) {
	uint16_t* memory = VIDEO_MEMORY;
	for (size_t y = 0; y < VGA_HEIGHT ; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			memory[index]  = frame.buffer[index];
		}
	}
}

