#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"
#include "stack_int.h"

#define SIZE (50)

static void StackSortTest(void);
static int IsStackSorted(int *arr, size_t size, stack_t *stack);
static int IsSmaller(const void *a, const void *b);
static void StackSortRandomTest(void);
static void StackSortReverse(void);

int main (void)
{
    int i = 0; 
    int j = 5; 
    StackSortTest();    
    StackSortRandomTest();
    StackSortReverse();
    puts("FFFFFF");

    return (EXIT_SUCCESS);
}

static int IsStackSorted(int *arr, size_t size, stack_t *stack)
{
    size_t i = 0;

    assert(arr);
    for (i = 0; i < size; ++i)
    {
        StackPopInt(stack, &arr[i]);
    }

    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            return 0; 
        }
    }

    return 1; 
}

static void StackSortTest(void)
{
    int arr[] = {5, 14, 12, 16, 18, 1, 4, 6, 8, 1, 0, 15 };
    int i = 0; 
    stack_t *stack = StackIntCreate(50);
    for (i = 0; i < 10; ++i)
    {
        StackPushInt(stack, arr[i]);
    }

    StackSortRec(stack); 
    if(0 == IsStackSorted(arr, 10 ,stack))
    {
        puts("Sort Test Failed");
    }

    StackDestroy(stack);
}

static void StackSortRandomTest(void)
{
    int arr[SIZE] = {0};
    int i = 0; 
    stack_t *stack = StackIntCreate(50);
    
    for (i = 0; i < 10; ++i)
    {
        arr[i] = rand () % 150; 
        StackPushInt(stack, arr[i]);
    }

    StackSortRec(stack); 
    if (0 == IsStackSorted(arr, SIZE, stack))
    {
        puts ("RAND TEST FAILS");
    }

    StackDestroy(stack);
}

static void StackSortReverse(void)
{
    int arr[SIZE] = {0}; 
    int i = 0; 
    stack_t *stack = StackIntCreate(SIZE);

    for (i = 0; i < SIZE; ++i)
    {
        arr[i] = rand() % 150; 
    }

    qsort(arr, SIZE, sizeof(int), IsSmaller);

    for (i = 0; i < SIZE; ++i)
    {
        StackPushInt(stack, arr[i]); 
    }

    StackSortRec(stack);
    if(0 == IsStackSorted(arr, SIZE, stack))
    {
        puts("Reverse Test Fail");
    }

    StackDestroy(stack);
}

static int IsSmaller(const void *a, const void *b)
{
    assert(a && b);
    return (*(int*)a < *(int*)b);
}
