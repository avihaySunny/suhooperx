
static unsigned int ByteMirrorLoop(unsigned int number)
{
    unsigned int mirror = 0;
    unsigned int byte = 0;
    int i = 0;

    for(; i < 3; ++i)
    {
        byte = number & 0xff ;
        mirror |= byte;
        mirror <<= 8;
        number >>= 8;
    }

    mirror |= number;

    return (mirror);
}


static unsigned int ByteMirror(unsigned int number)
{
    unsigned int byte1 = ((number & 0xff000000) >> 24);
    unsigned int byte2 = ((number & 0x00ff0000) >> 8);
    unsigned int byte3 = ((number & 0x0000ff00) << 8);
    unsigned int byte4 = ((number & 0x000000ff) << 24);

    return (byte1 | byte2 | byte3 | byte4);
}

unsigned int Sub(unsigned int x, unsigned int y ) /*calcs x-y */
{
   return (Add(x, AddOne(~y))); /* x - y = x + 2's_compliement(y) */
}

unsigned int Add(unsigned int x, unsigned int y) /* calc x+y */
{
    unsigned int sum = 0, carry = 0;
    
    sum = x ^ y;
    carry = x & y;
    while(0 != carry)
    {
        carry <<= 1 ;
        x = sum;
        y = carry;
        sum = x ^ y;
        carry = x & y;
    }
    
    return sum;
}

