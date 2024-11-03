#include "itoa.h"

int itoa_base(t_itoa_base base, char *buffer, int nb)
{
    if (nb == 0) {
        buffer[0] = base.buffer[0];
        return 0;
    }
    int next = nb / base.len;
    if (next) {
        int place = itoa_base(base, buffer, next);
        buffer[place] = base.buffer[nb % base.len];
        return 1 + place;
    }
    return 0;
}