module readline;

import utils::buffer;
import utils::printf;
import utils::window;
import utils::memory;
import utils::vector;
import std_io;
import terminal::ecma48;

const uint READLINE_BUFFER_SIZE = 1024;
const int FD = std_io::STD_OUT;

struct Buffer
{
    uint  caret_position;
    char[READLINE_BUFFER_SIZE]  b;
    Buffer(<char>)              buffer;
}

fn void Buffer.init(Buffer* this)
{
    this.buffer.data = &this.b;
    this.buffer.len = READLINE_BUFFER_SIZE;
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
	memory::set(<char>)(this.buffer.data, 0, 1); //~~??
}

fn void Buffer.on_backspace(Buffer* this, char c)
{
    if (this.caret_position = 0) return;

    this.buffer.remove(
        window::from_position(this.caret_position, -1),
		Buffer(<char>){1, 0, " "}
    );
    this.update_caret_position(-1);
    printf::dprintf(FD, "%c", c);
}

fn void Buffer.on_delete(Buffer* this, char c)
{
    if (this.caret_position == 0) return;

    this.buffer.remove(
        window::from_position(this.caret_position, 1),
		Buffer(<char>){1, 0, " "}
    );
    printf::dprintf(FD, "%c", c);
}

fn void Buffer.on_default(Buffer* this, char c)
{
    this.buffer.insert_one(this.caret_position, c);
    this.update_caret_position(+1);
    printf::dprintf(FD, "%c", c);
}

fn void Buffer.on_enter(Buffer* this, char c)
{
    this.buffer.insert_one(this.caret_position, '\n');
    // TODO: does readline need to forward this?
    // dprintf(fd, "%c", c);
}

fn void Buffer.on_cursor_mouvement(Buffer* this, Vec2 mouvement)
{
    if(this.update_caret_position(mouvement.x)) {
        ecma48::move_cursor(<Buffer>)(FD, mouvement.x, 0);
    }
}

fn void Buffer.readline(Buffer* this)
{
    Ecma48_handlers(<Buffer>) handlers = {
        .ref = this,
        .on_cursor_mouvement    = &Buffer.on_cursor_mouvement,
        .default_char_handler   = &Buffer.on_default,
        .char_handlers = {
            [0x08]  = &Buffer.on_backspace,
            [0x7F]  = &Buffer.on_delete, 
            [0x0A]  = &Buffer.on_enter,
        }
    };
    char[std_io::STD_IO_BUFFER_SIZE]    read_buffer;
    usz read_size = std_io::read(std_io::STD_IN, &read_buffer, std_io::STD_IO_BUFFER_SIZE);
    handlers.hooks(&read_buffer, read_size);
}
