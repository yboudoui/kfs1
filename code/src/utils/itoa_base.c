#include "itoa.h"

int itoa_base(t_itoa_base base, char *buffer, int nb)
{
    if (nb == 0)
        return 0;
    int place = itoa_base(base, buffer, nb / base.len);
    buffer[place] = base.buffer[nb % base.len];
    return 1 + place;
}