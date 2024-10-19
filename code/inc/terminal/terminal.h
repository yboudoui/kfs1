#include "vga.h"

typedef struct {
  size_t column, row;
} t_terminal_position;

typedef struct {
  t_vga_frame frame;
  t_vga_entry_color default_color;
  t_terminal_position current_position;
} t_terminal_frame;

t_terminal_frame* current_terminal_frame(t_terminal_frame* frame);
void terminal_frame_put_entry_at(t_vga_frame* frame, t_vga_entry entry, t_terminal_position position);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);
void terminal_update_frame(void);
void terminal_clear(void);
void terminal_reset_position(void);
