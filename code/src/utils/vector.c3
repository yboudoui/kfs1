module utils::vector;
import utils::memory;

def Vec2 = int[<2>];
def Fp_Set_Vec2 = fn void(Vec2*);

struct Clamped_Vec2
{
    Vec2 min, max, position;
}

fn void Clamped_Vec2.set_with_linear_position_by(Clamped_Vec2* this, int n)
{
    uint linear_position = this.get_linear_position();
    linear_position += n;
    this.position.x = linear_position % this.max.x;
    this.position.y = linear_position / this.max.x;
    this.update();
}

fn void Clamped_Vec2.update(Clamped_Vec2* this)
{
    clamp_vec2(&this.position, this.min, this.max);
}

fn uint Clamped_Vec2.get_linear_position(Clamped_Vec2* this)
{
    return this.position.y * this.max.x + this.position.x;
}

fn bool Clamped_Vec2.with(Clamped_Vec2* this, Fp_Set_Vec2... updates)
{
    Vec2 tmp = this.position;
    foreach (update : updates) update(&this.position);
    this.update();
    return (memory::compare(<Vec2>)(&this.position, &tmp, 1) == 0);
}

fn void clamp_int(int* value, int min, int max)
{
    if (*value < min) (*value) = min;
    if (*value > max) (*value) = max;
}

fn void clamp_vec2(Vec2* value, Vec2 min, Vec2 max)
{
    clamp_int(&value[0], min[0], max[0]);
    clamp_int(&value[1], min[1], max[1]);
}


fn void up          (Vec2* pos) { pos.y -= 1; }
fn void down        (Vec2* pos) { pos.y += 1; }
fn void left        (Vec2* pos) { pos.x -= 1; }
fn void right       (Vec2* pos) { pos.x += 1; }
fn void new_line    (Vec2* pos) { pos.x = 0; pos.y += 1; }