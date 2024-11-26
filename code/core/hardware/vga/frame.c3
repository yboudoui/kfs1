module vga;

const ushort*   VIDEO_MEMORY        = (ushort*)0xB8000;
const uint      MAX_WIDTH   = 80;
const uint      MAX_HEIGHT  = 25;
const uint      MAX_PRINTABLE_CHARACTER = MAX_WIDTH * MAX_HEIGHT;

import utils::memory;
import utils::window;
import utils::buffer;
import utils::vector;


// Declaration
struct Frame
{
  Clamped_Vec2                              cursor;
  Buffer(<Entry, MAX_PRINTABLE_CHARACTER>)  buffer;
}

fn void	Frame.init(Frame* this)
{
	this.cursor.max = Vec2{MAX_WIDTH, MAX_HEIGHT - 1};
	this.cursor.min = Vec2{0, 0};
}

fn void Frame.put_entry_at(Frame* this, Entry entry, Vec2 position)
{
	position.x %= MAX_WIDTH;
	position.y %= MAX_HEIGHT;
	uint index = position.y * MAX_WIDTH + position.x;
	this.buffer.data[index] = entry;
}

fn void Frame.fill(Frame* this, Entry entry)
{
    this.buffer.set(entry);
}

fn void Frame.main_frame_update(Frame* this)
{
    uint caret = this.cursor.get_linear_position();
	vga::set_cursor_position(caret);
	memory::copy(<Entry>)
    (
        destination:    VIDEO_MEMORY,
        source:         &this.buffer.data,
        count:          MAX_PRINTABLE_CHARACTER
    );
}

fn void Frame.remove(Frame* this, int nb, Entry default_entry)
{
    uint caret = this.cursor.get_linear_position();
    this.buffer.remove(
        window::from_position(caret, nb),
        &&Entry[1]{default_entry},
    );
}

fn void Frame.move_cursor_position_by(Frame* this, int n)
{
    this.cursor.set_with_linear_position_by(n);
}

fn void Frame.set_cursor_position(Frame* this, Vec2 position)
{
    this.cursor.position = position;
    this.cursor.update();
}

fn void Frame.put_entry(Frame* this, Entry entry)
{
    uint caret = this.cursor.get_linear_position();
    this.buffer.insert(caret, {entry});
}

fn bool Frame.next_line(Frame* this)
{
    return this.cursor.with(&vector::new_line);
}

fn bool Frame.move_cursor_up(Frame* this)
{
    return this.cursor.with(&vector::up);
}

fn bool Frame.move_cursor_down(Frame* this)
{
    return this.cursor.with(&vector::down);
}