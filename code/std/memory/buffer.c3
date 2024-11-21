module utils::buffer(<Type, MAX_CAPACITY>);

import utils::memory;
import utils::window;

struct Buffer {
    uint                size;
    Type[MAX_CAPACITY]  data;
}
                                                            
fn void Buffer.insert(Buffer* this, uint position, Type[] fill)
{ 
    if (position > this.data.len) return;
    
    memory::move(<Type>)
    (
        destination:    &this.data[position + fill.len],
        source:         &this.data[position],
        count:          this.data.len - (position + fill.len)
    );
    uint index_fill = 0;
    for (uint index = position; index < position + fill.len; index++)
    {
        index_fill          %= fill.len;
        this.data[index]    = fill[index_fill++];
    }                                                                                   
    this.size += fill.len;                                                           
}
                                                 
fn void Buffer.remove(Buffer* this, Window window, Type[] fill = {(Type)0})
{                                                           
    if (window.start > window.end) return;

    memory::move(<Type>)(
        destination:    &this.data[window.start],
        source:         &this.data[window.end],
        count:          this.data.len - window.end
    );
    uint index_fill = 0;
    for (uint index = (this.data.len - window.size()); index < this.data.len; index++)
    {
        this.data[index] = fill[index_fill];
        index_fill += 1;
        index_fill %= fill.len;
    }
    this.size -= window.size();
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