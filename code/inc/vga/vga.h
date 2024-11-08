#ifndef VGA_H
#define VGA_H

#include "constant.h"
#include "frame.h"
#include "color.h"
#include "cursor.h"


typedef struct {
  t_vec2      cursor;
  // size_t      caret;
  // t_vga_entry_color   default_color;
  t_vga_entry         buffer[VGA_MAX_PRINTABLE_CHARACTER];
} t_vga_frame;

t_vga_frame* current_vga_frame(t_vga_frame* vga_frame);
#define CURRENT_VGA_FRAME t_vga_frame* vga_frame = current_vga_frame(NULL);

void  vga_frame_put_entry_at(t_vga_entry entry, t_vec2 position);

void  vga_fill(t_vga_entry entry);
void  vga_main_frame_update(void);


void vga_frame_put_entry(t_vga_entry entry);
void vga_frame_remove(int nb, t_vga_entry default_entry);

// void vga_frame_putchar(char c);

#endif