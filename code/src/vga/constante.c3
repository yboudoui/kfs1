module vga::constante;

// Constante
const ushort*   VIDEO_MEMORY        = (ushort*)0xB8000;
const ushort    VGA_COMMAND_PORT    = 0x3D4;
const ushort    VGA_DATA_PORT       = 0x3D5;

const uint      VGA_WIDTH   = 80;
const uint      VGA_HEIGHT  = 25;
const uint      VGA_MAX_PRINTABLE_CHARACTER = VGA_WIDTH * VGA_HEIGHT;