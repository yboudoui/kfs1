module utils::clampe_value(<Type>);

fn void clamp(Type min, Type max, Type* value)
{
    if (*value < min) (*value) = min;
    if (*value > max) (*value) = max;
}


module utils::clamped_type(<Type, MIN, MAX>);

import utils::clampe_value;

distinct Clamped = Type;

fn Type Clamped.value(Clamped this)
{
    return (Type)this;
}

fn Type Clamped.set(Clamped* this, Type v)
{
    if (this.value() == v) return (Type)0;
    clampe_value::clamp(<Type>)(MIN, MAX, &v);
    *(Type*)this = v;
    return this.value();
}

fn Type Clamped.update(Clamped* this, Type v)
{
    return this.set(this.value() + v);
}

fn bool Clamped.is_min(Clamped this)
{
    return this.value() == MIN;
}

fn bool Clamped.is_max(Clamped this)
{
    return this.value() == MAX;
}

