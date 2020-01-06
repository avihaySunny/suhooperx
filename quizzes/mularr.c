#include <stdio.h>

int main (void)
{
    int arr1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int arr2[] = {1, 2, 3, 4, 0, 7, 8, 10, 5}; 
    int arr3[] = {1, 4, 7, 0, 9, 0, 3, 6, 7}; 
    long mul1[SIZE] = {0};
    long mul2[SIZE] = {0};
    long mul3[SIZE] = {0}; 

    MulArr(arr1, mul1, SIZE);
    MulArr(arr2, mul2, SIZE);
    MulArr(arr3, mul3, SIZE);

    PrintMulArr(mul1, SIZE);
    puts("--------------------");
    PrintMulArr(mul2, SIZE);
    puts("--------------------");
    PrintMulArr(mul3, SIZE);   

    return EXIT_SUCCESS;
}

static void PrintMulArr(long *arr, size_t size)
{
    size_t i = 0; 
    for (i = 0; i < size; ++i)
    {
        printf("%ld\n", arr[i]);
    }
}

static void MulArr(int *arr, long *mul, size_t size)
{
    long product = 1; 
    size_t i = 0; 
    int zeros = 0;
    int zerondx = 0;  

    for (i = 0; i < size; ++i)
    {
        if (0 == arr[i])
        {
            ++zeros;
            zerondx = i; 
            arr[i] = 1;
        }

        product *= arr[i];
    }
     
    /* memset(mul, 0, sizeof(long)* size); */
    
    for (i = 0; i < size && !zeros ; ++i)
    {
        mul[i] = product / arr [i] ; 
    } 

    if (zeros == 1)
    {
        mul[zerondx] = product;
    }

}