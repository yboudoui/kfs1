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
  uint                      caret;
}

fn int BufferIO.read(BufferIO* this, char *buffer, uint size)
{
    int bytes = string::len(&this.buffer);
    if (bytes >= size) bytes = size;

    memory::copy(<char>)(buffer, &this.buffer, bytes);
    if (size >= this.caret) {
         this.caret = 0;
    } else {
        this.caret -= size;
    }
   
    // TODO: memmove before memset remaining size
    memory::set(<char>)(&this.buffer, 0, STD_IO_BUFFER_SIZE);
    return bytes;
}

fn int BufferIO.write(BufferIO* this, char *buffer, uint size)
{
    if (size > STD_IO_BUFFER_SIZE - this.caret) return -1;
    memory::copy(<char>)(&this.buffer[this.caret], buffer, size);
    this.caret += size;
    return size;
}

struct StdIO
{
  BufferIO[3] fds;
}

fn StdIO* current_std_io(StdIO* std_io)
{
    static StdIO* current = null;
    if (std_io != null) {
        current = std_io;
    }
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

