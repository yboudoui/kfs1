#ifndef UTILS_ITOA_H
#define UTILS_ITOA_H

#include <stddef.h>

typedef struct {
    char    *buffer;
    size_t  len;
} t_itoa_base;

#define ITOA_BASE_DECIMAL       (t_itoa_base){"0123456789", 10}
#define ITOA_BASE_HEXADECIMAL   (t_itoa_base){"0123456789ABCDEF", 16}

void    itoa_base(t_itoa_base base, char *buffer, int nb);

#endif