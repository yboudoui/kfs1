#ifndef TERMINAL_H
#define TERMINAL_H

#include "vga.h"
#include "utils.h"
#include "keyboard.h"
#include "ecma48.h"
#include "std_io.h"


typedef struct s_terminal {
  t_vga_frame         vga_frame;
  t_vga_entry_color   default_color;
  t_fp_input_handler  input_handler;
  t_stdio             stdio;

  size_t              caret_position;

  // t_vec2              current_position;
} t_terminal;

t_terminal* current_terminal(t_terminal* frame);
#define CURRENT_TERMINAL t_terminal* terminal = current_terminal(NULL);

void  terminal_putchar_at(t_vec2 position, char c);
void  terminal_putchar(char c);
int   terminal_write(const char* data, size_t size);
void  terminal_put_block_at(size_t size, char* buffer, t_vec2 position);

void  terminal_clear(void);
void	terminal_update(void);

int terminal_write_2(const char* data, size_t size);

//
void terminal_init(t_vga_entry_color default_color, t_fp_input_handler input_handler);


extern char* KEYY;
#endif