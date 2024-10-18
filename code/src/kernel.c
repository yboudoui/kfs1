#include "kernel.h"

void kernel_main() {
  const char *message = "Hello, World odessein!";
  int i = 0;
  uint16_t *video_memory = (uint16_t *)VIDEO_MEMORY;

  while (message[i] != '\0') {
    video_memory[i] =
        vga_entry(message[i], (t_vga_entry_color){.fg = VGA_COLOR_RED,
                                                  .bg = VGA_COLOR_DARK_GREY});
    i++;
  }

  // Halt the CPU (loop indefinitely)
  while (1) {
  }
}
