#ifndef VGA_CURSOR_H
#define VGA_CURSOR_H

#include "vectors.h"
#include "constant.h"

#include <stdint.h>
#include <stddef.h>

/*
* Sources:
*   https://wiki.osdev.org/Text_Mode_Cursor
*/

void vga_disable_cursor(void);
void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);
void vga_set_cursor_position(t_vec2 position);

t_vec2 get_cursor_position(void);

#define VGA_DISABLE_CURSOR vga_disable_cursor();
#define VGA_ENABLE_CURSOR vga_enable_cursor(14, 15);

#endif