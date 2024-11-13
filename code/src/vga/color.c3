module vga::color;

enum Color : int 
{
    BLACK,         
    BLUE,          
    GREEN,         
    CYAN,          
    RED,           
    MAGENTA,       
    BROWN,         
    LIGHT_GREY,    
    DARK_GREY,     
    LIGHT_BLUE,    
    LIGHT_GREEN,    
    LIGHT_CYAN,     
    LIGHT_RED,      
    LIGHT_MAGENTA,  
    LIGHT_BROWN,    
    WHITE,          
}

struct Entry_color {
    Color foreground;
    Color background;
}

def Entry = ushort;

fn Entry entry(char uc, Entry_color color)
{
    char entry_color = (char)((int)color.foreground | (int)color.background << 4);
    return (ushort)uc | (ushort)entry_color << 8;
}