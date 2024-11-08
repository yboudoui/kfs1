#include "buffer.h"

t_window window_from_position(int position, int relative)
{
    if (relative < 0)
        return (t_window){position + relative, position};
    return (t_window){position, position + relative};
}

size_t window_size(t_window win)
{
    return win.end - win.start;
}