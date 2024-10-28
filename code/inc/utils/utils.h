#ifndef UTILS_H
#define UTILS_H

#include "itoa.h"
#include "memset.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>


size_t  strlen(const char* str);

void	*memcpy(void *dest, const void *src, size_t n);
void	*memmove(void *dest, const void *src, size_t n);
int     printf(const char *str, ...);
#endif