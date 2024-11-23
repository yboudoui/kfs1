module readline;

import utils::buffer;
import utils;
import utils::string;
import std_io;


const uint READLINE_BUFFER_SIZE = 1024;

struct Readline
{
    Buffer(<char, READLINE_BUFFER_SIZE>)    buffer;
    uint                                    caret_position;
}

fn void Readline.reset(Readline* this)
{
    this.buffer.clear();
}

fn void Readline.readline(Readline* this)
{
    readline::handler::HANDLER.hooks_fd(this, std_io::STD_IN);
}

module readline::handler;

import utils::vector;
import utils::window;
import utils::string;
import std_io;
import ecma48;

const int FD = std_io::STD_OUT;

const Ecma48_handlers(<Readline>) HANDLER = {
    .on_cursor_mouvement    = &Readline.on_cursor_mouvement,
    .default_char_handler   = &Readline.on_default,
    .char_handlers = {
        [0x08]              = &Readline.on_backspace,
        [0x7F]              = &Readline.on_delete,
        [0x0A]              = &Readline.on_enter,
    }
};

fn int Readline.update_caret_position(Readline* this, int n)
{
    int  old_position   = this.caret_position;
    int  new_position   = old_position + n;

    if (new_position < 0) new_position = 0;
    if (new_position > this.buffer.size) new_position = this.buffer.size;

    this.caret_position = new_position;
    return (old_position - new_position);
}

const int	TABSIZE = 4;

fn void Readline.on_backspace(Readline* this, char c)
{
    if (this.caret_position == 0) return;

	int len = (this.buffer.data[this.caret_position - 1] == '\t') ? TABSIZE : 1;

    this.buffer.remove(window::from_position(this.caret_position, -1));
    this.update_caret_position(-1);

    for (usz i = 0; i < len; i++) string::dprintf(FD, "%c", c);
}

fn void Readline.on_delete(Readline* this, char c)
{
    if (this.caret_position == this.buffer.size) return;

	int len = (this.buffer.data[this.caret_position - 1] == '\t') ? TABSIZE : 1;

    this.buffer.remove(window::from_position(this.caret_position, 1));

    for (usz i = 0; i < len; i++) string::dprintf(FD, "%c", c);
}

fn void Readline.on_default(Readline* this, char c)
{

    this.buffer.insert(this.caret_position, {c});
    this.update_caret_position(+1);

	if (this.buffer.data[this.caret_position - 1] == '\t') {
        ecma48::handler::move_cursor(FD, Vec2{+TABSIZE, 0});
    }
    else {
        utils::string::dprintf(FD, "%c", c);
    }
}

fn void Readline.on_enter(Readline* this, char c)
{
    this.buffer.insert(this.caret_position, {'\n'});
    string::dprintf(FD, "%c", c);
}

fn void Readline.on_cursor_mouvement(Readline* this, Vec2 mouvement)
{
    if(this.update_caret_position(mouvement.x) != 0) {
        ecma48::handler::move_cursor(FD, Vec2{mouvement.x, 0});
    }
}