module hardware;

// Extern C
extern fn void outb(ushort port, char data);
extern fn char inb (ushort port);

// fn char inb (ushort port) @inline
// {
//     char _v;
//     asm
//     {
//         in _v, (port);
//     }
//     return _v;
// } 