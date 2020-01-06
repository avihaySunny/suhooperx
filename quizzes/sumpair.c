#include <stdio.h>
#include <stdlib.h>

long *SumPair(int *arr, size_t num_of_elements)
{
    long *sum = (long*)arr;
    size_t i = 0; 
    
    for (i = 0; i < num_of_elements; i+=2, ++sum)
    {
        *sum = (long)arr[i] + (long)arr[i+1];
    }
    
    return ((long*)arr);
}

int main (void)
{
    int i = 0; 
    int arr[] = {0x7fffffff, 0x7fffffff, 456, -3, 8, 12};
    long *sum = SumPair(arr, 6); 
    
    for (i = 0; i < 3; ++i)
    {
        printf("%ld\n", *sum); 
        ++sum; 
    }
    
    return EXIT_SUCCESS;
    
}
