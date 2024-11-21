module utils::string;

// Basic string manipulation

fn uint len(char* str) 
{
	uint len = 0;
	while (str[len] != '\0') len++;
	return len;
}

fn int  compare(char *s1, char *s2)
{
	while ((*s1 || *s2))
	{
		if (*s1 != *s2) return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}

// Char predicat

fn bool    is_digit(int c)
{
	return (c >= '0' && c <= '9');
}

fn bool    is_space(int c)
{
    return (c >= '\t' && c <= '\r') || c == ' ';
}

fn bool    is_cntrl(int c)
{
    return (c >= 0 && c <= 31) || (c == 127);
}


// Number operations

fn int basic_atoi(int* result, char* buffer)
{
    int index;
    (*result) = 0;

    for(index = 0; is_digit(buffer[index]); index++) {
        (*result) = (*result * 10) + (buffer[index] - '0');
    }
    return index;
}

fn void atoi(int* result, char** buffer)
{
	int     sign;
    char*   tmp = (*buffer);

    while(is_space(*tmp)) tmp += 1;

    if (*tmp == '+') sign = +1;
    if (*tmp == '-') sign = -1;
    if (sign) tmp += 1;

    while(is_digit(*tmp))
    {
        (*result) = (*result * 10) + (*tmp++ - '0');
    }
    if (sign) (*result) *= sign;
    (*buffer) = tmp;
}

fn int itoa_base(char[] base, char *buffer, int nb)
{
    if (nb == 0) {
        buffer[0] = base[0];
        return 1;
    }
    int next = nb / base.len;
    int place = itoa_base(base, buffer, next);
    if (next == 0) place = 0;
    buffer[place] = base[nb % base.len];
    return 1 + place;
}

const char[] LOWER_HEXA_BASE  = "0123456789abcdef";
const char[] UPPER_HEXA_BASE  = "0123456789ABCDEF";
const char[] DECIMAL_BASE  = "0123456789";

// fn void! test_itoa_base_convert() @test
// {
//     char[64]    buffer;
//     int value;
//     int result;

//     DECIMAL.convert(&buffer, 42);
//     assert(compare(&buffer, "42") == 0, "Itoa_base.convert value:42 test:ok");
//     assert(compare(&buffer, "42") != 0, "Itoa_base.convert value:42 test:ko");
// }