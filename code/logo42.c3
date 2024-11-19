module kernel;

import terminal;
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



fn void putchar_at(Terminal *terminal, Vec2 position, char c)
{
	Entry entry = vga::entry(c, terminal.default_color);
    terminal.vga_frame.put_entry_at(entry, position);
}

fn void	put_block_at(Terminal *terminal, uint size, char* buffer, Vec2 position)
{
	Vec2 tmp;

	for (uint index = 0; index < size; index++)
	{
		if(buffer[index] == '\n')
		{
			tmp.x = 0;
			tmp.y += 1;
			continue;
		}
        putchar_at(terminal, position + tmp, buffer[index]);
		tmp.x += 1;
	}
}

fn void put_logo(Terminal* terminal)
{
	usz logo_len = string::len(LOGO);
	Vec2 logo_position = {
		(vga::MAX_WIDTH - 25) / 2,
		(vga::MAX_HEIGHT - 7) / 2,
	};
	put_block_at(terminal, logo_len, LOGO, logo_position);
}