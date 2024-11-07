#ifndef STD_IO_H
#define STD_IO_H

#include <stddef.h>

#define STD_IO_BUFFER_SIZE 1024

#define STD_OUT 0
#define STD_IN  1
#define STD_ERR 2

typedef struct s_io {
  char    buffer[STD_IO_BUFFER_SIZE];
  size_t  caret;
} t_io;

typedef struct s_stdio {
  t_io fds[3];
} t_stdio;

t_stdio* current_stdio(t_stdio* stdio);
#define CURRENT_STDIO t_stdio* stdio = current_stdio(NULL);

int read(int fd, char *buffer, size_t size);
int write(int fd, char *buffer, size_t size);

#endif