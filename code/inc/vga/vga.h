#ifndef VGA_H
#define VGA_H

#include "constant.h"
#include "frame.h"
#include "color.h"
#include "cursor.h"

typedef struct {
  t_vec2      cursor;
  t_vga_entry buffer[VGA_MAX_PRINTABLE_CHARACTER];
} t_vga_frame;

void  vga_frame_put_entry_at(t_vga_frame* vga_frame, t_vga_entry entry, t_vec2 position);

void  vga_main_frame_update(t_vga_frame vga_frame);
void  vga_fill(t_vga_frame* vga_frame, t_vga_entry entry);

#endif