#include "std_io.h"
#include "utils.h"

t_stdio* current_stdio(t_stdio* stdio)
{
    static t_stdio* current_stdio = NULL;

    if (stdio != NULL) {
        current_stdio = stdio;
    }
    return current_stdio;
}

int read(int fd, char *buffer, size_t size)
{
    CURRENT_STDIO

    int bytes = strlen(stdio->std_io[fd]);
    if (bytes >= size)
        bytes = size;

    memcpy(buffer, stdio->std_io[fd], bytes);
  
    // TODO: memmove before memset remaining size
    memset(char)(stdio->std_io[fd], 0, STD_IO_BUFFER_SIZE);
    return bytes;
}

int write(int fd, char *buffer, size_t size)
{
    CURRENT_STDIO
    // TODO:have to drop the memset
    memset(char)(stdio->std_io[fd], 0, STD_IO_BUFFER_SIZE);
    memcpy(stdio->std_io[fd], buffer, size);
    return size;
}