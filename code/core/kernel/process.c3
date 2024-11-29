module kernel::process;

import kernel::buffer_io;
import keyboard::scancode;
import tty;


const uint MAX_BUFFER_IO = 8;

def Fp_callback = fn void ();


def ProcessId = int;

struct Process
{
    ProcessId id;
    Fp_callback call;

    BufferIO[MAX_BUFFER_IO] fds;

    Tty tty;
}