#include "readline.h"

void readline(t_fp_get_character handler)
{
	char c = 0;

    while (1)
	{
		c = keyboard_handler();
		if (c != 0) {
			if (handler(c)) {
				return ;
			}
			c = 0;
		}
	}
}