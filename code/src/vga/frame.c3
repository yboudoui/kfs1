module vga::frame;

import vga::color;
import vga::constante;

import utils::memory;
import utils::window;
import utils::buffer;
import utils::vector;

import hardware;


// Declaration
struct Frame
{
  vector::Clamped_Vec2      cursor;
  Entry[constante::VGA_MAX_PRINTABLE_CHARACTER] b;
  Buffer(<Entry>)   buffer;
} 

fn void	Frame.init(Frame* this)
{
    this.buffer.len = constante::VGA_MAX_PRINTABLE_CHARACTER;
    this.buffer.data = &this.b;
	this.cursor.max = Vec2{constante::VGA_WIDTH, constante::VGA_HEIGHT - 1};
	this.cursor.min = Vec2{0, 0};
}

fn void Frame.put_entry_at(Frame* this, Entry entry, Vec2 position)
{
	position.x %= constante::VGA_WIDTH;
	position.y %= constante::VGA_HEIGHT;
	uint index = position.y * constante::VGA_WIDTH + position.x;
	this.buffer.data[index] = entry;
}

fn void Frame.fill(Frame* this, Entry entry)
{
    this.buffer.clear(entry);
}

fn void Frame.set_cursor_position(Frame* this)
{
    uint caret = this.cursor.get_linear_position();

    // Send the high byte of the cursor position to VGA port 0x3D4 (index 0x0E)
    hardware::outb(constante::VGA_COMMAND_PORT, 0x0E);
    hardware::outb(constante::VGA_DATA_PORT, (char)(caret >> 8) & 0xFF);  // High byte

    // Send the low byte of the cursor position to VGA port 0x3D4 (index 0x0F)
    hardware::outb(constante::VGA_COMMAND_PORT, 0x0F);
    hardware::outb(constante::VGA_DATA_PORT, (char)(caret & 0xFF));  // Low byte
}

fn void Frame.main_frame_update(Frame* this)
{
	this.set_cursor_position();
	memory::copy(<Entry>)
    (
        destination:    constante::VIDEO_MEMORY,
        source:         this.buffer.data,
        count:          constante::VGA_MAX_PRINTABLE_CHARACTER
    );
}

fn void Frame.remove(Frame* this, int nb, Entry default_entry)
{
    Buffer(<Entry>) tmp_fill = {
        .len = 1,
        .size = 0,
        .data = &default_entry,
    };
    uint caret = this.cursor.get_linear_position();
    this.buffer.remove(
        window::from_position(caret, nb),
        tmp_fill,
    );
}

fn void Frame.move_cursor_position_by(Frame* this, int n)
{
    this.cursor.set_with_linear_position_by(n);
}

fn void Frame.put_entry(Frame* this, Entry entry)
{
    uint caret = this.cursor.get_linear_position();
    this.buffer.insert_one(caret, entry);
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