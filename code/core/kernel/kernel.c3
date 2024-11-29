module kernel;
import kernel::process;

import ecma48;
import std_io;
import keyboard;


const uint MAX_PROCESS = 8;

struct Kernel
{
    Process[MAX_PROCESS]    process_table;
    uint                    process_count;
    ProcessId               current;
}

fn ProcessId Kernel.new_process(Kernel *this, Fp_callback call)
{
    this.process_table[this.process_count] = {
        .id     = this.process_count,
        .call   = call,
    };

    this.set_current_process_id(this.process_count);
    defer this.process_count += 1;
    return this.process_count;
}

fn ProcessId Kernel.get_current_process_id(Kernel this)
{
    return this.current;
}

fn void Kernel.set_current_process_id(Kernel* this, ProcessId id)
{
    this.current = id;
}

fn int Kernel.read(Kernel* this, int fd, char* buffer, uint size)
{
    return this.process_table[this.current].fds[fd].read(buffer, size);
}

fn int Kernel.write(Kernel* this, int fd, char* buffer, uint size)
{
    return this.process_table[this.current].fds[fd].write(buffer, size);
}

fn void Kernel.run_process(Kernel* this)
{
    Process c = this.process_table[this.current];
    this.set_current_process_id(c.id);
    c.call();
}

Kernel main = {};
