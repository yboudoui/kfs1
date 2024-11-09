#ifndef VGA_CURSOR_H
#define VGA_CURSOR_H

#include "vectors.h"
#include "constant.h"

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>


/*
* Sources:
*   https://wiki.osdev.org/Text_Mode_Cursor
*/

void vga_disable_cursor(void);
void vga_enable_cursor(uint8_t cursor_start, uint8_t cursor_end);

#define VGA_DISABLE_CURSOR  vga_disable_cursor();
#define VGA_ENABLE_CURSOR   vga_enable_cursor(14, 15);

bool vga_frame_move_cursor_up(void);
bool vga_frame_move_cursor_down(void);
void vga_frame_move_cursor_position_by(int n);

#endif