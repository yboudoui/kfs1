#include "atoi.h"

bool    is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

bool    is_space(int c)
{
    return (c >= '\t' && c <= '\r') || c == ' ';
}

void atoi(int* result, char**buffer)
{
	int	sign;
    char* tmp = (*buffer);

    while(is_space(*tmp)) tmp += 1;

	sign = (*tmp == '+') - (*tmp == '-');
	tmp += (!!sign);

    while(is_digit(*tmp))
    {
        (*result) = (*result * 10) + (*tmp++ - '0');
    }
	(*result) *= ((!!sign) * sign) + (!sign);
    (*buffer) = tmp;
}