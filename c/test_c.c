#include <stdio.h> 
#include <stdlib.h> 

#define BYTE (8)
long Fibonacci(unsigned int n)
{
    unsigned int i = 0; 
    long old_sum = 0, sum = 1; 
    
    if (!n)
    {   
        return old_sum; 
    }

    for (i = 1; i < n; ++i)    
    {
        sum += old_sum; 
        old_sum = sum - old_sum; 
        printf("old sum : %ld\n", old_sum);
        printf("sum : %ld\n", sum);
    }
    
    return sum; 
}

char *IntToString(int number)
{
    char *buffer = malloc (250); 
    sprintf(buffer,"%d",number); 
    
    return buffer; 
}

int FlipVal(int number)
{
    int minus = 0, mirror = 0; 
    
    if(number < 0)
    {
        minus = 1; 
        number *= -1; 
    }
    
    while (0 != number)
    {
        mirror = mirror * 10 + number % 10;
        number /= 10;  
    }
    
    if (minus)
    {
        mirror *=-1; 
    }
    
    return mirror; 
}



int main (void)
{
    printf("%d\n",FlipVal(-1423)); 
    
    return 0; 
}
