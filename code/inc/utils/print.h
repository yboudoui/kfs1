#ifndef UTILS_PRINT_H
#define UTILS_PRINT_H

#include <stdarg.h>

int     vdprintf(int fd, const char *str, va_list tab);
int     vsprintf(char* buffer, const char *str, va_list	tab);

int     dprintf(int fd, const char *str, ...);
int     sprintf(char* buffer, const char *str, ...);

int     printf(const char *str, ...);
int     printk(const char *str, ...);

#endif