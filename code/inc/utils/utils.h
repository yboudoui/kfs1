#ifndef UTILS_H
#define UTILS_H

#include "itoa.h"
#include "memset.h"
#include "atoi.h"
#include <stdint.h>
#include <stdarg.h>


size_t  strlen(const char* str);

void	*memcpy(void *dest, const void *src, size_t n);
void	*memmove(void *dest, const void *src, size_t n);
int     printf(const char *str, ...);

int     strcmp(const char *s1, const char *s2);

#endif