module hardware;

// Extern C
fn void outb(ushort _port, ushort _data) @inline
{
    asm
    {
        movw    $ax , _data;
        movw    $dx , _port;
    }
    asm("out %ax, %dx");
}

fn ushort inb (ushort _port) @inline
{
    ushort _v;
    asm
    {
        movw    $dx , _port;
        in      _v  , $dx;
    }
    return _v;
} 