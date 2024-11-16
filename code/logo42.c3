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


fn void put_logo(Terminal* terminal)
{
	usz logo_len = string::len(LOGO);
	Vec2 logo_position = {
		(vga::MAX_WIDTH - 25) / 2,
		(vga::MAX_HEIGHT - 7) / 2,
	};
	terminal.put_block_at(logo_len, LOGO, logo_position);
}