#include <stdio.h>

static int MaxSubArray (int arr[], int size,int *right, int *left) 
{
    int max_now = 0; 
    int max_end = 0; 
    int i = 0; 
    
    for (i =0; i < size; ++i)
    {
        max_end = max_end + arr[i];
        if(max_end < 0)
        {
            max_end = 0; 
            *left = i + 1; 
        }
        
        if(max_now < max_end)
        {
            max_now = max_end; 
            *right = i; 
        }
    }
    
    return max_now; 
}

int main (void)
{
    int arr[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4}; 
    int size = 9; 
    int a = 0, b = 0; 
    int max = MaxSubArray(arr, size, &a, &b);
    
    printf("a = %d\nb = %d\nmax = %d",a, b, max);

}
