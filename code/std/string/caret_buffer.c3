module utils::string::caret_buffer(<Type, BUFFER_SIZE>);

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
    inline Buffer(<Type, BUFFER_SIZE>) buffer;
    Clamped(<0, BUFFER_SIZE>)   caret_position;
}

fn void CaretBuffer.reset(CaretBuffer* this)
{
    this.buffer.clear();
    this.caret_position.set(0);
}

fn int CaretBuffer.update_caret(CaretBuffer* this, int n = 0)
{
    if (n > 0 && this.caret_position == this.buffer.size) return 0;
    if (this.caret_position.can_be_updated_by(n) == false) return 0;
    return this.caret_position.update(n);
}

fn int! CaretBuffer.select(CaretBuffer* this, Type[] buffer, int n = 0)
{
    if (n == 0) return 0;
    int len = math::abs(n);
    if (len > buffer.len) return Err.UNABLE_TO_SELECT?;

    int max = this.caret_position;
    if (n > 0) max = this.buffer.size - max;
    
    clampe_value::clamp(<int>)(0, max, &len);
    
    Type* source = &this.buffer.data[this.caret_position];
    if (n < 0) source -= len;
    memory::copy(<Type>)(buffer, source, len);

    return (n < 0) ? -len : len;
}

fn int CaretBuffer.remove(CaretBuffer* this, int n = 0)
{
    if (n > this.buffer.size) return 0;
    if (this.caret_position.can_be_updated_by(n) == false) return 0;
    this.buffer.remove(this.caret_position.get_range_relative_to(n));
    if (n < 0) this.caret_position.update(n);
    return (n);
}

fn int CaretBuffer.insert(CaretBuffer* this, Type[] str)
{
    return this.caret_position.update(this.buffer.insert(this.caret_position, str));
}