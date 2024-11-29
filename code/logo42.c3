module kernel;

import tty;
import vga;
import utils::vector;
import utils::string;

const char* LOGO = `
        :::      ::::::::
      :+:      :+:    :+:
    +:+ +:+         +:+  
  +#+  +:+       +#+     
+#+#+#+#+#+   +#+        
     #+#    #+#          
    ###   ########.fr    `;



fn void putchar_at(Tty *tty, Vec2 position, char c)
{
	Entry entry = vga::entry(c, tty.default_color);
    tty.vga_frame.put_entry_at(entry, position);
}

fn void	put_block_at(Tty *tty, uint size, char* buffer, Vec2 position)
{

	// TODO: need to add the width with in printf in order for this code to work
	
	// char* line = buffer;
	// for(int y = position.y; &buffer[size] - line; y++) {
	// 	char* new_line = memory::search(line, '\n', &buffer[size] - line);
	// 	string::dprintf(0, "\e[%d%dH%*.s", y, position.x, new_line - line, line);
	// 	line = new_line;
	// }
	

	Vec2 tmp;

	for (uint index = 0; index < size; index++)
	{
		if(buffer[index] == '\n')
		{
			tmp.x = 0;
			tmp.y += 1;
			continue;
		}
        putchar_at(tty, position + tmp, buffer[index]);
		tmp.x += 1;
	}
}

fn void put_logo(Tty* tty)
{
	usz logo_len = string::len(LOGO);
	Vec2 logo_position = {
		(vga::MAX_WIDTH - 25) / 2,
		(vga::MAX_HEIGHT - 7) / 2,
	};
	put_block_at(tty, logo_len, LOGO, logo_position);
}