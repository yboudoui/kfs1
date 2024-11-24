module utils::string::caret_buffer(<BUFFER_SIZE>);

import utils::math;
import utils::buffer;
import utils::window;
import utils::memory;
import utils::clampe_value;
import utils::clamped_type;

fault Err
{
    UNABLE_TO_SELECT,
}

struct CaretBuffer
{
    Buffer(<char, BUFFER_SIZE>)     buffer;
    Clamped(<uint, 0, BUFFER_SIZE>) caret_position;
}

fn int! CaretBuffer.select(CaretBuffer* this, char[] buffer, int count = 0)
{
    if (count == 0) return 0;
    int len = math::abs(count);
    if (len > buffer.len) return Err.UNABLE_TO_SELECT?;

    int max = this.caret_position.value();
    if (count > 0) max = this.buffer.size - max;
    
    clampe_value::clamp(<int>)(0, max, &len);
    
    char* source = &this.buffer.data + this.caret_position.value();
    if (count < 0) source -= len;
    memory::copy(<char>)(buffer, source, len);

    return (count < 0) ? -len : len;
}

fn int CaretBuffer.remove(CaretBuffer* this, int n = 0)
{
    // TODO: Need to return the amount of character effectivily removed
    if (n == 0) return 0;
    if (this.caret_position.is_min()) return 0;
    if (this.caret_position.is_max()) return 0;

    // TODO: need to give to the user a way to know what will be deleted

	// int len = 1;
    // if (this.caret_position > 0 && this.buffer.data[this.caret_position - 1] == '\t') len = TABSIZE;

    this.buffer.remove(window::from_position(this.caret_position.value(), n));
    if (n < 0) this.caret_position.update(n);
    return (n); //?/
}

fn int CaretBuffer.insert(CaretBuffer* this, char[] str)
{
    if (this.caret_position.is_max()) return 0;
    int len = this.buffer.insert(this.caret_position.value(), str);
    return this.caret_position.update(len);
}