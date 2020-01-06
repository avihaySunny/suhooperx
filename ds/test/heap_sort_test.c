/*******************************************************************************
* Programmer: Avihay Asraf
* heap_sort_test.c
* File: heap_sort testing
* Date: ד' יונ 26 22:16:45 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include "heap_sort.h"


#define RANGE (500)
#define Q_SIZE (5000)

static int IsBefore(const void *dataA, const void *dataB);
static int IsBeforeInt(const int *dataA, const int *dataB);
static void FillArray(int *arr, size_t size);
static int IsSorted(int *arr, size_t size);
static void TestHeapSort(void);

int main(void)
{
    TestHeapSort();
    return (EXIT_SUCCESS);
}

static void TestHeapSort(void)
{
    int heap_arr[Q_SIZE]  = {0}; 
    size_t i = 0; 
    FillArray(heap_arr, Q_SIZE); 
    
    HeapSort(heap_arr, Q_SIZE, sizeof(int), IsBefore);
    if (!IsSorted(heap_arr, Q_SIZE))
    {
        puts("Not Sorted");
    }

    for (i = 0; i < Q_SIZE; ++i)
    {
        printf("%d\n", heap_arr[i]);
    }
}

static int IsBefore(const void *dataA, const void *dataB)
{
    return IsBeforeInt(dataA, dataB);
}

static int IsBeforeInt(const int *dataA,const int *dataB)
{
    return(*dataA < *dataB);
}

static void FillArray(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);
    
    for (i = 0; i < size; ++i)
    {
        arr[i] = rand() % RANGE; 
    }
}

static int IsSorted(int *arr, size_t size)
{
    size_t i = 0;

    assert(arr);

    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            return 0;
        }
    }

    return 1; 
}
