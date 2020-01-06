/****************************************************************************/
/*                                   StackTests.c                           */
/*                                   Avihay Asraf                           */
/*                                    May 2019                              */
/*                                  Data Structurs                          */  
/****************************************************************************/
#include <stdio.h>          /*printf, puts          */
#include <stdlib.h>         /*EXIT_SUCCESS/FAIL     */

#include "./include/stack.h"

#define N_ELEMENTS (5)

static void StackPushTest(void);
static void StackPeekPopTest(void);
static void StackCreateTest(void);

int main (void)
{
    StackCreateTest();
    StackPushTest();
    StackPeekPopTest();
    
    return (EXIT_SUCCESS); 
}

static void StackPushTest(void)
{
    int i = 0;
    stack_t *sp = StackCreate(N_ELEMENTS, sizeof(int));
    if(NULL == sp)
    {
        puts("Stack Create Fail");
        return; 
    }
    
    puts("StackPush:");
    
    for (i = 0; i < N_ELEMENTS; ++i)
    {
        StackPush(sp, &i); 
    }
 
    (StackIsFull(sp) ? puts("PUSH SUCCESS"): puts("PUSH FAIL"));
    StackDestroy(sp);   
    sp = NULL;
}    
    
static void StackPeekPopTest(void)   
{
    int arr[N_ELEMENTS] = {0};
    int i = 0, b = 0, pop_fail = 1; 
    stack_t *sp = StackCreate(N_ELEMENTS, sizeof(int));
    if(NULL == sp)
    {
        puts("Stack Create Fail");
        return; 
    }

    puts("StackPop:");
    
    for (i = 0; i < N_ELEMENTS; ++i)
    {
        StackPush(sp, &i); 
        arr[i] = i; 
    }
        
    for (i = N_ELEMENTS - 1; i >= 0 && (1 == pop_fail); --i)
    {
        StackPeek(sp, &b);
        (b == arr[i]) ? (pop_fail = 1):(pop_fail = 0);
        StackPop(sp);
    }
 
    (StackIsEmpty(sp)) ? puts("STACK EMPTY SUCCES"):puts("STACK EMPTY FAIL");
    StackDestroy(sp);       
    sp = NULL;
}

static void StackCreateTest(void)
{
    stack_t *sp = StackCreate(N_ELEMENTS, sizeof(int));
    if (NULL != sp)
    {
        puts("STACK CREATE SUCCESS"); 
    }    
    else
    {
        puts("STACK CREATE FAIL");
    }
    
    StackDestroy(sp);
    sp = NULL; 
}

 
