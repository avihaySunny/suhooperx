#include <stdlib.h>
#include <stdio.h> 

#define MAX(a,b) ((a > b) ? (a) : (b))
#define Q_SIZE (50)
static void Swap(int *a, int *b); 

void BubbleSort(int arr[], size_t arr_size)
{

    size_t i = 0, j = 0;   

    for (i = 0; i < arr_size; ++i)
    { 
        for (j = 0; j < arr_size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1]) 
            {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }

}

void SelectionSort(int arr[], size_t arr_size)
{
    int min = arr[0]; 
    size_t i = 0, j = 0;
    for (i = 0; i < arr_size; ++i)
    {
        for (j = i; j < arr_size; ++j)
        {
            if (arr[j] < min)
            {
                Swap(&arr[j], &min);
            }
        }

        Swap(&arr[i], &min);
    }
}

void CountingSort(int arr[], size_t arr_size)
{
    
}
static void Swap(int *a, int *b)
{
    int temp = *a; 
    *a = *b; 
    *b = temp;
}

int main (void)
{
    size_t size = Q_SIZE; 
    static int arr[Q_SIZE] = {0}; 
    size_t i = 0;

    for (i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100; 
    } 

    for (i = 0; i < size; ++i)
    {
        printf("%d\n", arr[i]); 
    } 

    SelectionSort(arr, size);
    
    puts("------------------------------");
    for (i = 0; i < size; ++i)
    {
        printf("%d\n", arr[i]); 
    }
  
    return EXIT_SUCCESS; 
}