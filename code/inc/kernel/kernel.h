#ifndef KERNEL_H
#define KERNEL_H

#include "utils.h"

void bootloader_screen(void);
void kernel_main(void);

void *global_data_pointer(void *data);
#endif