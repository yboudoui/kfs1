#include "ui_box.h"

#include "utils.h"
#include "terminal.h"

static void dump_line(char** buffer, size_t size, char border_set[3])
{
    (*buffer)[0] = border_set[0];
    memset(char)((*buffer) + 1, border_set[1], size - 2);
    (*buffer)[size - 1] = border_set[2];
    (*buffer)[size] = '\n';
    (*buffer) += size + 1;
}

void print_ui_box(t_ui_box ui_box)
{
    char buffer[VGA_MAX_PRINTABLE_CHARACTER] = {0};
    char *line = buffer;
    char box_border_set[3][3] = {
        {0xDA, 0xC4, 0xBF},
        {0xB3, 0x20, 0xB3},
        {0xC0, 0xC4, 0xD9},
    };

    dump_line(&line, ui_box.outer_size.x, box_border_set[0]);
    for (size_t y = 0; y < ui_box.outer_size.y - 1; y++) {
        dump_line(&line, ui_box.outer_size.x, box_border_set[1]);
        // buffer[] = box_border_set[1][0];
        // memcpy(buffer + 1, )
        // buffer[] = box_border_set[1][2];
    }
    dump_line(&line, ui_box.outer_size.x, box_border_set[2]);

    terminal_put_block_at(buffer, ui_box.position);
}