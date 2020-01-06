/****************************************************************************/
/*                                   StackTests.h                           */
/*                                   Avihay Asraf                           */
/*                                    May 2019                              */
/*                                  Data Structurs                          */  
/****************************************************************************/
#ifndef __STACK_TEST_H__
#define __STACK_TEST_H__  

typedef struct stack stack_t;  

typedef enum
{
    STACK_SUCCESS,
    STACK_OVERFLOW,
    STACK_UNDERFLOW
} stack_status_t;   

stack_t *StackCreate(size_t n_elements, size_t element_size);

void StackDestroy(stack_t *stack_p);

stack_status_t StackPush(stack_t *stack_p, const void *data); 

stack_status_t StackPop(stack_t *stack_p);

int StackIsFull(const stack_t *stack_p);

int StackIsEmpty(const stack_t *stack_p);

stack_status_t StackPeek(const stack_t *stack_p, void *dest);

size_t StackSize(const stack_t *stack_p);

#endif /* __STACK_TEST_H__*/
