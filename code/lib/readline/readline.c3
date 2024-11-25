module readline;

import utils::buffer;
import utils;
import utils::string;
import std_io;

const uint READLINE_BUFFER_SIZE = 1024;

struct Readline
{
    inline CaretBuffer(<char, READLINE_BUFFER_SIZE>) b;
}

fn void Readline.readline(Readline* this)
{
    readline::handler::HANDLER.hooks_fd(this, std_io::STD_IN);
}

module readline::handler;

import utils::vector;
import utils::window;
import utils::string;
import utils::math;
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

const int	TABSIZE = 4;

fn void Readline.on_backspace(Readline* this, char c)
{
    char[1] tmp;
    this.b.select(&tmp, -1)!!;
    if(!this.b.remove(-1)) return;

    int len = (tmp[0] == '\t') ? TABSIZE : 1;
    while (len--) std_io::write(FD, char[]{0x08}, 1);
}

fn void Readline.on_delete(Readline* this, char c)
{
    char[1] tmp;
    this.b.select(&tmp, 1)!!;
    if(!this.b.remove(1)) return;

    int len = (tmp[0] == '\t') ? TABSIZE : 1;
    while (len--) std_io::write(FD, char[]{0x7F}, 1);
}

fn void Readline.on_default(Readline* this, char c)
{
    if (!this.b.insert({c})) return;

    int len = (c == '\t') ? TABSIZE : 1;
    c = (c == '\t') ? ' ' : c;

    while (len--) std_io::write(FD, char[]{c}, 1);
}

fn void Readline.on_enter(Readline* this, char c)
{
    this.b.insert({'\n'}); // Will be removed or not
    std_io::write(FD, char[]{0x0A}, 1);
}

fn void Readline.on_cursor_mouvement(Readline* this, Vec2 mouvement)
{
    char[1] tmp;
    int len = math::abs(mouvement.x);
    int dir = (mouvement.x < 0) ? -1 : 1;

    while (len--) {
        this.b.select(&tmp, dir)!!;
        if(!this.b.update_caret(dir)) return;
        int direction = (tmp[0] == '\t') ? (TABSIZE * dir) : dir;
        ecma48::handler::move_cursor(FD, Vec2{direction, 0});
    }
}