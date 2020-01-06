#include <stdio.h>

typedef struct location
{
    int x; 
    int y;
} loc_t; 

int IsSumFound(loc_t *loc, int arr[], int sum, size_t size)
{
    int left = 0, right = size - 1, ar_sum = 0; 
    
    while (right < left)
    {
        ar_sum = arr[right] + arr[left]; 
        if(ar_sum < sum)
        {
            ++right; 
        }
        
        if(ar_sum > sum)
        {
            --left; 
        }    
    }
    
    loc-> x = right; 
    loc-> y = left; 
    
    return (right < left);
}


