#include <stddef.h>
#include <stdint.h>
#define VIDEO_MEMORY (uint16_t*)0xB8000

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_MAX_PRINTABLE_CHARACTER VGA_WIDTH * VGA_HEIGHT

typedef enum {
  VGA_COLOR_BLACK = 0,
  VGA_COLOR_BLUE = 1,
  VGA_COLOR_GREEN = 2,
  VGA_COLOR_CYAN = 3,
  VGA_COLOR_RED = 4,
  VGA_COLOR_MAGENTA = 5,
  VGA_COLOR_BROWN = 6,
  VGA_COLOR_LIGHT_GREY = 7,
  VGA_COLOR_DARK_GREY = 8,
  VGA_COLOR_LIGHT_BLUE = 9,
  VGA_COLOR_LIGHT_GREEN = 10,
  VGA_COLOR_LIGHT_CYAN = 11,
  VGA_COLOR_LIGHT_RED = 12,
  VGA_COLOR_LIGHT_MAGENTA = 13,
  VGA_COLOR_LIGHT_BROWN = 14,
  VGA_COLOR_WHITE = 15,
} t_vga_color;

typedef struct {
  t_vga_color fg;
  t_vga_color bg;
} t_vga_entry_color;

typedef uint16_t t_vga_entry;

typedef struct {
  uint16_t buffer[VGA_MAX_PRINTABLE_CHARACTER];
} t_vga_frame;

static inline t_vga_entry vga_entry(unsigned char uc, t_vga_entry_color color)
{
  uint8_t entry_color = color.fg | color.bg << 4;
  return (uint16_t)uc | (uint16_t)entry_color << 8;
}

void vga_main_frame_update(t_vga_frame frame);
