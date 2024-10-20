#ifndef VGA_CONSTANT_H
#define VGA_CONSTANT_H

#define VIDEO_MEMORY (uint16_t*)0xB8000

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define VGA_MAX_PRINTABLE_CHARACTER VGA_WIDTH * VGA_HEIGHT

#define VGA_COMMAND_PORT 0x3D4
#define VGA_DATA_PORT    0x3D5

#endif