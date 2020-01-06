#include <stdlib.h> /* malloc 	*/
#include <stdio.h> 	/* fprintf 	*/
#include <assert.h> /* assert 	*/
#include <string.h> /* memcpy 	*/

#include "stack.h"

#define HEAD(sp) (void *)((size_t)sp + sizeof(stack_t)) 

struct stack  
{  
    void *tail; 
    void *current; 
    size_t element_size; 
}; 

stack_t *StackCreate(size_t n_elements, size_t element_size)
{
	stack_t *sp = (stack_t *)malloc(n_elements * element_size + sizeof(stack_t));
	if (NULL == sp)
	{
		return (NULL);
	}

	sp->tail = (char *)sp + n_elements * element_size + sizeof(stack_t);
	sp->current = HEAD(sp);
	sp->element_size = element_size;

	return (sp);
}

void StackDestroy(stack_t *stack_p)
{
	if (NULL != stack_p)
	{
		stack_p->tail = NULL;
		stack_p->current = NULL;

		free(stack_p);
		stack_p = NULL;		
	}
}

stack_status_t StackPush(stack_t *stack_p, const void *data)
{
	assert(stack_p);

	if (StackIsFull(stack_p))
	{
		return STACK_OVERFLOW;
	}

	memcpy(stack_p->current, data, stack_p->element_size);
	stack_p->current = (char *)stack_p->current + stack_p->element_size;
	
	return (STACK_SUCCESS);
}

stack_status_t StackPeek(const stack_t *stack_p, void *dest)
{
	assert(stack_p);

	if (StackIsEmpty(stack_p))
	{
		return (STACK_UNDERFLOW);
	}

	memcpy(dest, 
		(char *)stack_p->current - stack_p->element_size, 
		stack_p->element_size);

	return (STACK_SUCCESS);
}

stack_status_t StackPop(stack_t *stack_p)
{
	assert(stack_p);

	if (StackIsEmpty(stack_p))
	{
		return (STACK_UNDERFLOW);
	}

	stack_p->current = (char *)stack_p->current - stack_p->element_size;

	return STACK_SUCCESS;
}


/*****************************************************************/

size_t StackSize(const stack_t *stack_p)
{
	assert(stack_p);

	return ((size_t)stack_p->current - (size_t)HEAD(stack_p)) / stack_p->element_size;
}


int StackIsEmpty(const stack_t *stack_p)
{
	assert(stack_p);

	return stack_p->current == HEAD(stack_p);
}

int StackIsFull(const stack_t *stack_p)
{
	assert(stack_p);

	return stack_p->current == stack_p->tail;
}
