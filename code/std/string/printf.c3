module utils::string;

import std_io;
import utils::memory;

const uint BUFFER_SIZE = 2048;

def Fp_dump = fn int(char*, any);

fn int dump_character(char *buffer, any arg)
{
	char* character = (char*)arg;
	buffer[0] = *character;
	return 1;
}

fn int dump_string(char *buffer, any arg)
{
	char** str = (char**)arg;

	uint	size = string::len(*str);
	memory::copy(<char>)(buffer, *str, size);
	return size;
}

fn int dump_pointer(char *buffer, any arg)
{
	ulong* address = (ulong*)arg;

	if (*address == 0) {
		memory::copy(<char>)(buffer, "0x0", 3);
		return (3);
	}
	memory::copy(<char>)(buffer, "0x", 2);
	return (string::LOWER_HEXA.convert(buffer + 2, (int)*address) + 2);
}

fn int dump_number(char *buffer, any arg)
{
	int* number = arg.ptr;

    // TODO: Clean this
	int is_negative = 0;
	if (*number < 0)
	{
		*number *= -1;
		buffer[0] = '-';
		// memcpy(buffer, "-", 1);
		is_negative = 1;
	}
	return (string::DECIMAL.convert(buffer + is_negative, *number)) + is_negative;
}

fn int dump_unsigned_number(char *buffer, any arg)
{
	int* number = (int*)arg;
	return (string::DECIMAL.convert(buffer, *number));
}

fn int dump_lower_hexadecimal_case(char *buffer, any arg)
{
	uint* number = (uint*)arg;
	return (string::LOWER_HEXA.convert(buffer, *number));
}

fn int dump_upper_hexadecimal_case(char *buffer, any arg)
{
	uint* number = (uint*)arg;
	return (string::UPPER_HEXA.convert(buffer, *number));
}

fn int dump_percentage(char *buffer, any arg)
{
	buffer[0] = '%';
	return 1;
}

fn int	vsprintf(char* buffer, char* str, any[] args)
{
	if (!buffer || !str) return (-1);

	static Fp_dump[128] dispatch;
	dispatch['c'] = &dump_character;
	dispatch['s'] = &dump_string;
	dispatch['p'] = &dump_pointer;
	dispatch['i'] = &dump_number;
	dispatch['d'] = &dump_number;
	dispatch['u'] = &dump_unsigned_number;
	dispatch['x'] = &dump_lower_hexadecimal_case;
	dispatch['X'] = &dump_upper_hexadecimal_case;
	dispatch['%'] = &dump_percentage;
	

	int		len = 0;
	int		i = 0;
	char	current, next;

	for (usz index = 0; str[index] != '\0'; index++)
	{
		current = str[index];
		next = str[index + 1] ? str[index + 1] : '\0';
		if (current == '%' && dispatch[next])
		{
			len += dispatch[next](&buffer[len], args[i]);
			index += 1;
			i += 1;
		}
		else
		{
			buffer[len] = current;
			len += 1;
		}
	}
	return (len);
}

fn int vdprintf(int fd, char* str, any[] args)
{
	char[BUFFER_SIZE]	buffer;

	int len = vsprintf(&buffer, str, args);
    if (len < 0) return len;
    return (std_io::write(fd, &buffer, len));
}

fn int dprintf(int fd, char* str, args...)
{
	return vdprintf(fd, str, args);
}

fn int	sprintf(char* buffer, char *str, args...)
{
	return vsprintf(buffer, str, args);
}

fn int	printf(char *str, args...)
{
	return vdprintf(std_io::STD_OUT, str, args);
}

// import terminal;
// fn int	printk(char *str, args...)
// {
// 	char[BUFFER_SIZE]	buffer @noinit;

// 	int len = vsprintf(&buffer, str, args);
//     if (len < 0) return len;
// 	terminal::write(&buffer, len);
//     return len;
// }