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

    int bytes = strlen(stdio->fds[fd].buffer);
    if (bytes >= size)
        bytes = size;

    memcpy(buffer, stdio->fds[fd].buffer, bytes);
    if (size >= stdio->fds[fd].caret)
         stdio->fds[fd].caret = 0;
    else
        stdio->fds[fd].caret -= size;
   
    // TODO: memmove before memset remaining size
    memset(char)(stdio->fds[fd].buffer, 0, STD_IO_BUFFER_SIZE);
    return bytes;
}

int write(int fd, char *buffer, size_t size)
{
    CURRENT_STDIO

    if (size > STD_IO_BUFFER_SIZE - stdio->fds[fd].caret)
        return -1;
    memcpy(&stdio->fds[fd].buffer[stdio->fds[fd].caret], buffer, size);
    stdio->fds[fd].caret += size;
    return size;
}