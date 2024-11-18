module readline;

import utils::buffer;
import utils::string;
import utils::window;
import utils::memory;
import utils::vector;
import std_io;
import terminal::ecma48;

const uint READLINE_BUFFER_SIZE = 1024;
const int FD = std_io::STD_OUT;

struct Buffer
{
    Ecma48_handlers(<Buffer>)               ecma48_handlers;
    uint                                    caret_position;
    Buffer(<char, READLINE_BUFFER_SIZE>)    buffer;
}

fn void Buffer.init(Buffer* this)
{
    this.ecma48_handlers = {
        .ref = this,
        .on_cursor_mouvement    = &Buffer.on_cursor_mouvement,
        .default_char_handler   = &Buffer.on_default,
        .char_handlers = {
            [0x08]    = &Buffer.on_backspace,
            [0x7F]    = &Buffer.on_delete,
            [0x0A]    = &Buffer.on_enter,
        }
    };
}

fn int Buffer.update_caret_position(Buffer* this, int n)
{
    int  old_position   = this.caret_position;
    int  new_position   = old_position + n;

    if (new_position < 0) {
        new_position = 0;
    }
    if (new_position > this.buffer.size) {
        new_position = this.buffer.size;
    }

    this.caret_position = new_position;
    return (old_position - new_position);
}

fn void Buffer.reset(Buffer* this)
{
    this.buffer.clear();
}

fn void Buffer.on_backspace(Buffer* this, char c)
{
    if (this.caret_position == 0) return;

    this.buffer.remove(
        window::from_position(this.caret_position, -1),
        " "
    );
    this.update_caret_position(-1);
    string::dprintf(FD, "%c", c);
}

fn void Buffer.on_delete(Buffer* this, char c)
{
    if (this.caret_position == 0) return;

    this.buffer.remove(
        window::from_position(this.caret_position, 1),
        " "
    );
    string::dprintf(FD, "%c", c);
}

fn void Buffer.on_default(Buffer* this, char c)
{
    this.buffer.insert(this.caret_position, {c});
    this.update_caret_position(+1);
    string::dprintf(FD, "%c", c);
}

fn void Buffer.on_enter(Buffer* this, char c)
{
    this.buffer.insert(this.caret_position, {'\n'});
    // TODO: does readline need to forward this?
    string::dprintf(FD, "%c", c);
}

fn void Buffer.on_cursor_mouvement(Buffer* this, Vec2 mouvement)
{
    if(this.update_caret_position(mouvement.x) != 0) {
        ecma48::move_cursor(<Buffer>)(FD, x:mouvement.x);
    }
}

fn void Buffer.readline(Buffer* this)
{
    static char[std_io::STD_IO_BUFFER_SIZE]    read_buffer;
    int read_size = std_io::read(
        std_io::STD_IN,
        &read_buffer,
        std_io::STD_IO_BUFFER_SIZE
    );
    this.ecma48_handlers.hooks(&read_buffer, read_size);
}
