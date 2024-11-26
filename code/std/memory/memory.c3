module utils::memory(<Type>);

fn void     zero(Type* destination, uint count)
{
    char *tmp = (char*)destination;
    count *= Type.sizeof;
    for (uint index = 0; index < count; index++)
    {
        tmp[index] = 0;
    }                 
}

fn void* memset(void* dest, int value, usz n) @export("memset") @nostrip
{
    char *src = (char*)dest;
    for (uint index = 0; index < n; index++)
    {
        src[index] = (char)value;
    }
    return dest;
}

fn void* memcpy(void* dest, void* src, usz n) @export("memcpy") @nostrip
{
    if (dest == null || src == null) return dest;

    char* destination = (char*)dest;
    char* source = (char*)src;
    for (uint index = 0; index < n; index++)
    {
        destination[index] = source[index];
    }
	return (destination);
}

fn void     set(Type* destination, Type value, uint count) 
{
    for (uint index = 0; index < count; index++)
    {
        destination[index] = value;
    }                 
}

fn Type*    search(Type* source, Type value, uint count)
{
    for (usz i; i < count; i++) if (source[i] == value) return source + i;
    return null;
}

fn Type*    copy(Type* destination, Type* source, uint count)
{
	if (!destination || !source || !count) return (destination);
    for (uint i = 0; i < count; i++) destination[i] = source[i];
	return (destination);
}

fn Type*    move(Type* destination, Type* source, uint count)
{        
	if (!destination || !source) return (destination);

	int     direction   = 1;
    uint    index       = 0;
    if (destination > source)
    {
        direction   = -1;
        index       = count - 1;
    }            
	while (count--)
    {
		destination[index] = source[index];                         
		index += direction;                                                 
	}                                                                       
    return (destination);                                                          
}

fn int      compare(Type* s1, Type* s2, uint n)
{
    char *ptr1 = (char*)s1;
    char *ptr2 = (char*)s2;
    
    n *= Type.sizeof;

	for (uint index = 0; index < n; index++)
    {
        if (ptr1[index] != ptr2[index])
        {
            return (ptr1[index] - ptr2[index]);
        }
	}
	return (0);
}
