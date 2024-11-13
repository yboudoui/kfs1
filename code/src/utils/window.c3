module utils::window;

struct Window {
    int start, end;
}

fn Window from_position(int position, int relative)
{
    if (relative < 0) return Window{position + relative, position};
    return Window{position, position + relative};
}

fn uint Window.size(Window* this)
{
    return this.end - this.start;
}