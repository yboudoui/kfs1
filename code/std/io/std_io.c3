module std_io;

import utils::string;
import utils::memory;

const uint STD_IO_BUFFER_SIZE = 1024;

const uint STD_OUT = 0;
const uint STD_IN  = 1;
const uint STD_ERR = 2;

struct BufferIO
{
  char[STD_IO_BUFFER_SIZE]  buffer;
  uint                      size;
}

fn int BufferIO.read(BufferIO* this, char *buffer, uint size)
{
    if (size > this.size) size = this.size;
    
    memory::copy(<char>)(buffer, &this.buffer, size);
    memory::move(<char>)(&this.buffer, &this.buffer[size], STD_IO_BUFFER_SIZE - size);
    memory::set(<char>)(&this.buffer[STD_IO_BUFFER_SIZE - 1 - size], (char)0, size);

    this.size -= size;
    return size;
}

fn int BufferIO.write(BufferIO* this, char *buffer, uint size)
{
    if (size > STD_IO_BUFFER_SIZE) size = STD_IO_BUFFER_SIZE;

    memory::copy(<char>)(&this.buffer[this.size], buffer, size);

    this.size += size;
    return size;
}

struct StdIO
{
  BufferIO[3] fds;
}

fn StdIO* current_std_io(StdIO* std_io)
{
    static StdIO* current = null;
    if (std_io != null) current = std_io;
    return current;
}

fn int read(int fd, char* buffer, uint size)
{
    StdIO* stdio = current_std_io(null);

    if (stdio == null) return -1;
    return stdio.fds[fd].read(buffer, size);
}

fn int write(int fd, char* buffer, uint size)
{
    StdIO* stdio = current_std_io(null);

    if (stdio == null) return -1;
    return stdio.fds[fd].write(buffer, size);
}

