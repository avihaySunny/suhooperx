#include <stdio.h>

#include "stack.h"
#include "stack_int.h"

void StackSortRec(stack_t *stack);

stack_t *StackIntCreate(size_t n_elements)
{
    stack_t *stack = StackCreate(n_elements, sizeof(int));
    if (!stack)
    {
        return NULL; 
    }

    return stack; 
}

int StackIntIsEmpty(const stack_t *stack)
{
    return StackIsEmpty(stack);
}

void StackPopInt(stack_t *stack ,int *num)
{
    StackPeek(stack, num);
    StackPop(stack);
}

void StackPushInt(stack_t *stack, int num)
{
    StackPush(stack, &num); 
}

size_t StackSizeInt(const stack_t *stack)
{
    return StackSize(stack);
}

void StackSortRec(stack_t *stack)
{
    int num = 0; 
    int stack_top = 0; 

    if (StackSizeInt(stack) == 1)
    {
        return; 
    }
    else 
    {
        StackPopInt(stack, &num); 
        StackSortRec(stack);
    } 

    StackPopInt(stack, &stack_top);

    if (num > stack_top)
    {
        StackPushInt(stack, stack_top);
        StackPushInt(stack, num);
    }
    else
    {
        StackPushInt(stack, num);
        StackSortRec(stack);
        StackPushInt(stack, stack_top);
    }
}
