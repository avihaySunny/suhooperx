#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>


const size_t num_to_divide = 5754853344;
void *ThreadSumOfDividers(const void *range);
size_t sum_of_dividers = 0; 

int main (void)
{
    size_t i = 0; 
    size_t reminder = 0;
    size_t end = num_to_divide; 
    
    #pragma omp parallel for 
    for (i = 1; i <= end; ++i)
    {
        if (0 == (reminder = num_to_divide % i))
        {
            printf("%ld\n", i);
            sum_of_dividers += i;
        }
    }
    
    printf("%ld\n", sum_of_dividers);

    return EXIT_SUCCESS;
}


void *ThreadSumOfDividers(const void *range)
{ 
    const size_t end = *(const size_t*)range; 
    size_t reminder = 0; 
    size_t i = 0; 

    for (i = 1; i <= end; ++i)
    {
        if (0 == (reminder = num_to_divide % i))
        {
            printf("%ld\n", i);
            sum_of_dividers += i;
        }
    }

    return (void*)range;
}