module std_io;
import kernel;

const uint STD_IO_BUFFER_SIZE = kernel::buffer_io::IO_BUFFER_SIZE;
const uint STD_OUT = 0;
const uint STD_IN  = 1;
const uint STD_ERR = 2;

fn int read(int fd, char* buffer, uint size)
{
    return kernel::main.read(fd, buffer, size);
}

fn int write(int fd, char* buffer, uint size)
{
    return kernel::main.write(fd, buffer, size);
}

