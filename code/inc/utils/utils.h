#ifndef UTILS_H
#define UTILS_H

#include "itoa.h"
#include "memset.h"
#include <stdbool.h>
#include <stdint.h>

size_t  strlen(const char* str);

// void    *memset(char c, void *buffer, size_t len);
void	*memcpy(void *dest, const void *src, size_t n);
void	*memmove(void *dest, const void *src, size_t n);

#endif