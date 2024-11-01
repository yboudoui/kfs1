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

int read(t_stdio_fd fd, char *buffer, size_t size)
{
    CURRENT_STDIO
    memcpy(buffer, stdio->std_io[fd], size);
}

int write(t_stdio_fd fd, char *buffer, size_t size)
{
    CURRENT_STDIO
    memcpy(stdio->std_io[fd], buffer, size);
}