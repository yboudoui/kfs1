#include "vga.h"

static inline t_vga_entry vga_entry(unsigned char uc, t_vga_entry_color color) {
  uint8_t entry_color = color.fg | color.bg << 4;
  return (uint16_t)uc | (uint16_t)entry_color << 8;
}

void vga_main_frame_update(t_vga_frame frame) {
	uint16_t* memory = VIDEO_MEMORY;
	for (size_t y = 0; y < frame.height ; y++) {
		for (size_t x = 0; x < frame.width; x++) {
			const size_t index = y * frame.width + x;
			memory[index]  = frame.buffer[index];
		}
	}
}

