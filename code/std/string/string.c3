module utils::string;

// Basic string manipulation

fn uint len(char* str) 
{
	uint len = 0;
	while (str[len] != '\0') len++;
	return len;
}

fn int  strcmp(char *s1, char *s2)
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

struct Itoa_base
{
    char    *buffer;
    uint    len;
}

fn int Itoa_base.convert(Itoa_base this, char *buffer, int nb)
{
    if (nb == 0) {
        buffer[0] = this.buffer[0];
        return 0;
    }
    int next = nb / this.len;
    if (next) {
        int place = this.convert(buffer, next);
        buffer[place] = this.buffer[nb % this.len];
        return 1 + place;
    }
    return 0;
}

const Itoa_base LOWER_HEXA  = {"0123456789abcdef",  16};
const Itoa_base UPPER_HEXA  = {"0123456789ABCDEF",  16};
const Itoa_base DECIMAL     = {"0123456789",        10};