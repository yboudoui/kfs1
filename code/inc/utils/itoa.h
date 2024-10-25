#ifndef UTILS_ITOA_H
#define UTILS_ITOA_H

#include <stddef.h>

typedef struct {
    char    *buffer;
    size_t  len;
} t_itoa_base;

#define ITOA_BASE_DECIMAL       (t_itoa_base){"0123456789", 10}
#define ITOA_BASE_HEXADECIMAL   (t_itoa_base){"0123456789ABCDEF", 16}

int    itoa_base(t_itoa_base base, char *buffer, int nb);


#define DECLARE_ITOA_BASE(name, base) \
inline static int itoa_##name(char *buffer, int nb) { \
    if (nb == 0) return 0; \
    int place = itoa_##name(buffer, nb / (sizeof(base) - 1)); \
    buffer[place] = base[nb % (sizeof(base) - 1)]; \
    return 1 + place; \
}

DECLARE_ITOA_BASE(lower_hexa, "0123456789abcdef")
DECLARE_ITOA_BASE(upper_hexa, "0123456789ABCDEF")
DECLARE_ITOA_BASE(decimal, "0123456789")

#endif