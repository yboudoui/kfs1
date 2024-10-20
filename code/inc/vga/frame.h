#ifndef VGA_FRAME_H
#define VGA_FRAME_H

#include "constant.h"
#include "memset.h"
#include "color.h"

#include <stdint.h>
#include <stddef.h>

typedef uint16_t t_vga_entry;

DECLARE_MEMSET(t_vga_entry)

static inline t_vga_entry vga_entry(unsigned char uc, t_vga_entry_color color)
{
  uint8_t entry_color = color.fg | color.bg << 4;
  return (uint16_t)uc | (uint16_t)entry_color << 8;
}

#endif