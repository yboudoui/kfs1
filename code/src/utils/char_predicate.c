#include "char_predicate.h"

bool    is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

bool    is_space(int c)
{
    return (c >= '\t' && c <= '\r') || c == ' ';
}

bool    is_cntrl(int c)
{
    return (c >= 0 && c <= 31) || (c == 127);
}