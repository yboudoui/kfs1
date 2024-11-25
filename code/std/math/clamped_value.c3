module utils::clampe_value(<Type>);

fn void clamp(Type min, Type max, Type* value)
{
    if (*value < min) (*value) = min;
    if (*value > max) (*value) = max;
}


module utils::clamped_type(<MIN, MAX>);
import utils::clampe_value;
import utils::window;

def Clamped = int;

fn Clamped Clamped.set(Clamped* this, Clamped v)
{
    if (*this == v) return 0;
    clampe_value::clamp(<Clamped>)(MIN, MAX, &v);
    *this = v;
    return *this;
}

import utils::string;
fn Clamped Clamped.update(Clamped* this, Clamped v)
{
    if (this.can_be_updated_by(v)) {
    this.set(*this + v);
    return v;
    } 
    return 0;
}

fn bool Clamped.is_min(Clamped this)
{
    return this == MIN;
}

fn bool Clamped.is_max(Clamped this)
{
    return this == MAX;
}

fn bool Clamped.is_extremum(Clamped this)
{
    return this.is_max() || this.is_min();
}

fn bool Clamped.can_be_updated_by(Clamped this, Clamped n)
{
    // if (tmp == 0) return false;
    // if (tmp < 0 && this.is_min()) return false;
    // if (tmp > 0 && this.is_max()) return false;

    Clamped tmp = this + n;
    if (tmp < MIN) return false;
    if (tmp > MAX) return false;
    return true;
}

fn Window Clamped.get_range_relative_to(Clamped this, Clamped n)
{
    return window::from_position(this, n);
}