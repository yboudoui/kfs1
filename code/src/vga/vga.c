#include "vga.h"

static inline uint16_t vga_entry(unsigned char uc, t_vga_entry_color color) {
  uint8_t entry_color = color.fg | color.bg << 4;
  return (uint16_t)uc | (uint16_t)entry_color << 8;
}
