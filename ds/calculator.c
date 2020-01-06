/*******************************************************************************
* Programmer: Avihay Asraf
* calculator.c
* File: calculator code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#include "calculator.h"

typedef struct operator 
{
    char symbol;       /* mathe            */
    size_t precedence; /* which come first   */
    size_t asscoicate; /* left = 0, right = 1 */
    void (*operation)(void *, void*, void *);
}op_t;

static double Plus(const double x, const double y); 
static double Minus(const double x, const double y);
static double Mul(const double x, const double y);
static double Div(const double x, const double y);
static void SetOperator(op_t *op, char symbol, size_t prece, size_t assoc, double (*operation)(const double, const double));
void InitOperators();
static int TokenIsNum(char *token);

op_t op_list[60] = {0};

queue_t *ShuntingYard(char *expression)
{
    char *token = NULL; 
    const char *delim = " ";  
    char *op_ptr = NULL; 
    char *op_stack_top = NULL; 
    queue_t *output_q = QCreate();
    stack_t *op_stack = StackCreate(150, sizeof(char*));
    
    InitOperators();

    token = strtok(expression, delim);
    while(NULL != token)
    { 
        op_list[*token].operation(op_stack, output_q, token); 
        token = strtok(NULL, delim);
    }  

    while (!StackIsEmpty(op_stack))
    {
        StackPeek(op_stack, op_stack_top);
        StackPop(op_stack);
        QEnqueue(output_q, op_stack_top); 
    }

    return output_q;
}


double Plus(const double x, const double y)
{
    return (x + y); 
}

double Minus(const double x, const double y)
{
    return (x - y); 
}

double Mul(const double x, const double y)
{
    return (x * y); 
}

double Div(const double x, const double y)
{
    return (x / y);
}

void PushOntoQueue(void *stack, void *q, void *token)
{
    QEnqueue((queue_t*)q, token);
}

void PushOntoStack(void *stack, void *q, void *token)
{
    stack_t *op_stack = stack; 
    char *tok = token;  
    queue_t *queue = q;

    if (!StackIsEmpty(op_stack))
    {
        
    }   
}

void SetOperator(op_t *op, char symbol, size_t prece, size_t assoc, double (*operation)(const double, const double))
{
    op->symbol = symbol; 
    op->precedence = prece; 
    op->asscoicate = assoc; 
    op->operation = operation; 
}

void InitOperators()
{
    SetOperator(&op_list[48], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[49], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[50], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[51], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[52], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[53], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[54], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[55], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[56], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[57], 0,0,0, PushOntoQueue);
    SetOperator(&op_list[42], '*', 3, 0, PushOntoStack); 
    SetOperator(&op_list[43], '+', 2, 0, PushOntoStack); 
    SetOperator(&op_list[45], '-', 2, 0, PushOntoStack); 
    SetOperator(&op_list[47], '/', 3, 0, PushOntoStack); 
}

