#ifndef VGA_H
#define VGA_H

#include "constant.h"
#include "frame.h"
#include "color.h"
#include "cursor.h"

typedef struct s_vga_frame {
  t_clamped_vec2      cursor;
  t_vga_entry         buffer[VGA_MAX_PRINTABLE_CHARACTER];
} t_vga_frame;

t_vga_frame* current_vga_frame(t_vga_frame* vga_frame);
#define CURRENT_VGA_FRAME t_vga_frame* vga_frame = current_vga_frame(NULL);

void	vga_frame_init(t_vga_frame* vga_frame);


void  vga_frame_put_entry_at(t_vga_entry entry, t_vec2 position);
void  vga_frame_put_entry(t_vga_entry entry);

void  vga_fill(t_vga_entry entry);

void  vga_frame_remove(int nb, t_vga_entry default_entry);
bool  vga_frame_next_line(void);

void  vga_main_frame_update(void);
#endif