module utils::buffer(<Type, MAX_CAPACITY>);

import utils::memory;
import utils::window;

struct Buffer {
    uint                size;
    Type[MAX_CAPACITY]  data;
}

fn void Buffer.fill_remaining(Buffer* this, uint from, uint until, Type[] fill) @private
{
    uint index_fill = 0;
    for (uint index = from; index < until; index++)
    {
        this.data[index] = fill[index_fill];
        index_fill = (index_fill + 1) % fill.len;
    }
}

fn int Buffer.insert(Buffer* this, uint position, Type[] fill)
{
    if (position > this.data.len) return 0; // NOTE:Should return an error
    
    memory::move(<Type>)
    (
        destination:    &this.data[position + fill.len],
        source:         &this.data[position],
        count:          this.data.len - (position + fill.len)
    );
    this.fill_remaining(
        from:   position,
        until:  position + fill.len,
        fill:   fill
    );
    this.size += fill.len;
    return fill.len;
}
                                                 
fn int Buffer.remove(Buffer* this, Window window, Type[] fill = {(Type)0})
{                                                           
    if (window.start > window.end) return 0; // NOTE:Should return an error

    uint count = this.data.len - window.end;
    memory::move(<Type>)(
        destination:    &this.data[window.start],
        source:         &this.data[window.end],
        count:          count
    );
    this.fill_remaining(
        from:   count,
        until:  this.data.len,
        fill:   fill
    );
    this.size -= window.size();
    return window.size();
}

fn void Buffer.set(Buffer* this, Type fill)
{                                                           
	memory::set(<Type>)
    (
        destination:    &this.data,
        value:          fill,
        count:          this.data.len,
    );                                                        
}

fn void Buffer.clear(Buffer* this)
{
    Type empty;               
    this.set(empty);
}