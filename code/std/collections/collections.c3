module utils::collections(<Type>);

fault CollectionsResult
{
    NONE_OF,
}

fn int! one_of(Type[] array, Type value)
{
    foreach (i, el : array) if (el == value) return i;
    return CollectionsResult.NONE_OF?;
}