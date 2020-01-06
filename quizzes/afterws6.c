#include <stdio.h> 

int BitCoupleCount(unsigned char n)
{
    int count = 0; 
    
    while (0 != n)
    {
        count += ((n & 3) == 3);
        n >>= 1;  
    }
    
    return count; 
}

int main (void)
{
    printf("%d", BitCoupleCount(0x76));
    return 0; 
    
}
