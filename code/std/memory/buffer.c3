module utils::buffer(<Type>);

import utils::memory;
import utils::window;

struct Buffer {
    uint    len;
    uint    size;
    Type*   data;
}
                                                            
fn void Buffer.insert(Buffer* this, uint position, Buffer fill)
{ 
    if (position > this.len) return;

    memory::move(<Type>)
    (
        destination:    this.data + position + fill.len,
        source:         this.data + position,
        count:          this.len - (position + fill.len)
    );                                         
    uint index_fill = 0;
    for (uint index = position; index < position + fill.len; index++)
    {
        index_fill          %= fill.len;
        this.data[index]    = fill.data[index_fill++];
    }                                                                                   
    this.size += fill.len;                                                           
}

fn void Buffer.insert_one(Buffer* this, uint position, Type fill)
{
    Buffer(<Type>) tmp = {
        .len = 1,
        .data = Type[]{fill},
    };
    this.insert(position, tmp);
}
                                                 
fn void Buffer.remove(Buffer* this, Window window, Buffer fill)
{                                                           
    if (window.start > window.end) return ;                                             

    memory::move(<Type>)(                                                                      
        destination:    this.data + window.start,
        source:         this.data + window.end,
        count:          this.len - window.end
    );                                                      
    uint index_fill = 0;                                                              
    for (uint index = (this.len - window.size()); index < this.len; index++)
    {       
        index_fill %= fill.len;                                                         
        this.data[index] = fill.data[index_fill++];            
    }                                                                                   
    this.size -= window.size();                                                           
}

fn void Buffer.clear(Buffer* this, Type fill)
{                                                           
	memory::set(<Type>)
    (
        destination:    this.data,
        value:          fill,
        count:          this.len,
    );                                                        
}

