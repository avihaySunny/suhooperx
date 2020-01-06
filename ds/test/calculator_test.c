/*******************************************************************************
* Programmer: Avihay Asraf
* calculator_test.c
* File: calculator testing
* Date: ה' יונ 20 13:23:32 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include "calculator.h"

int main(void)
{
    char expression[] = "30 * 42 - 51 + 7";
    char *token = NULL; 
    queue_t *q =  ShuntingYard(expression);
    
    while (!QIsEmpty(q))
    {
        token = QDequeue(q); 
        printf("%s\n", token);
    }
    return (EXIT_SUCCESS);
}








