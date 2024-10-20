#include "itoa.h"

void swap(char* a, char* b)
{
    char temp = *a;
    *a = *b;
    *b = temp; 
}

void reverse_string(char *str, size_t length) {
    size_t start = 0;
    size_t end = length - 1;
    while (start < end) {
        swap(&str[start], &str[end]);
        start++;
        end--;
    }
}


void itoa_base(t_itoa_base base, char *buffer, int nb)
{
    size_t i = 0;

    while (nb > 0)
    {
        buffer[i++] = base.buffer[nb % base.len];
        nb /= base.len;
    }
    buffer[i] = 0;
    reverse_string(buffer, i);
}