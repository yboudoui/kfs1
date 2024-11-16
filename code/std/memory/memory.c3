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

fn void     set(Type* destination, Type value, uint count)
{
    for (uint index = 0; index < count; index++)
    {
        destination[index] = value;
    }                 
}

fn Type*    copy(Type* destination, Type* source, uint count)
{
	if (destination == null || source == null)
    {
        return (destination);
    }

    for (uint index = 0; index < count; index++)
    {
        destination[index] = source[index];
    }
	return (destination);
}

fn Type*    move(Type *destination, Type *source, uint count)
{        
	if (destination == null || source == null) return (destination);

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

fn int	compare(Type* s1, Type* s2, uint n)
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
