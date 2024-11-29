module kernel::buffer_io;

import utils::memory;

const uint IO_BUFFER_SIZE = 1024;

struct BufferIO
{
  uint                  size;
  char[IO_BUFFER_SIZE]  data;
}

fn int BufferIO.read(BufferIO* this, char *buffer, uint size)
{
    if (size > this.size) size = this.size;
    
    memory::copy(<char>)(buffer, &this.data, size);
    memory::move(<char>)(&this.data, &this.data[size], IO_BUFFER_SIZE - size);
    memory::set(<char>)(&this.data[IO_BUFFER_SIZE - 1 - size], (char)0, size);

    this.size -= size;
    return size;
}

fn int BufferIO.write(BufferIO* this, char *buffer, uint size)
{
    if (size > IO_BUFFER_SIZE) size = IO_BUFFER_SIZE;

    memory::copy(<char>)(&this.data[this.size], buffer, size);

    this.size += size;
    return size;
}
