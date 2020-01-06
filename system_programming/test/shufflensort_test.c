/*******************************************************************************
* Programmer: Avihay Asraf
* shufflensort_test.c
* File: shufflensort testing
* Date: ה' יול 18 15:27:48 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include "shufflensort.h"

static void PrintDictionary(char *wrd_ptr_list[], size_t size);
static int IsSorted(char *buffer[], size_t count); 

int main(void)
{
    size_t count = 0; 
    char *wrd_buff_ptrs[DIC_WRD_NUM * NUM_OF_COPIES] = {NULL};
    char *buffer = malloc(UPPER_LIMIT * DIC_WRD_NUM); 
    
    if (NULL == buffer)
    {
        return EXIT_FAILURE; 
    }

    ShuffleAndSort(wrd_buff_ptrs, buffer, &count); 
    printf("%d\n", IsSorted(wrd_buff_ptrs, count));
    PrintDictionary(wrd_buff_ptrs, count);

    free (buffer); 

    return (EXIT_SUCCESS);
}

static void PrintDictionary(char *wrd_ptr_list[], size_t size)
{   
    size_t i = 0; 
    for (i = 0; i < size; ++i)
    {
        printf("%s", wrd_ptr_list[i]);
    }
}

static int IsSorted(char *buffer[], size_t count)
{
    size_t i = 0; 
    for (i = 0; i < count - 1; ++i)
    {
        if (*buffer[i] > *buffer[i + 1])
        {
            return 0; 
        } 
    }

    return 1; 
}

