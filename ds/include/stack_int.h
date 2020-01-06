#include <stdio.h>

#include "stack.h"

void StackSortRec(stack_t *stack);

stack_t *StackIntCreate(size_t n_elements);

int StackIntIsEmpty(const stack_t *stack);
void StackPopInt(stack_t *stack ,int *num);
void StackPushInt(stack_t *stack, int num);
size_t StackSizeInt(const stack_t *stack);
void StackSortInt(stack_t *stack);