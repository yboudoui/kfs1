#ifndef STD_IO_H
#define STD_IO_H

#include <stddef.h>

#define STD_IO_BUFFER_SIZE 256

typedef enum s_stdio_fd {
  STDOUT,
  STDIN,
  STDERR,
  MAX_STD_IO,
} t_stdio_fd;

typedef struct s_stdio {
  char std_io[MAX_STD_IO][STD_IO_BUFFER_SIZE];
} t_stdio;

t_stdio* current_stdio(t_stdio* stdio);
#define CURRENT_STDIO t_stdio* stdio = current_stdio(NULL);

int read(t_stdio_fd fd, char *buffer, size_t size);
int write(t_stdio_fd fd, char *buffer, size_t size);

#endif