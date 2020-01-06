/*******************************************************************************
* Programmer: Avihay Asraf
* recursion.c
* File: recursion code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */
#include <sll.h>            /*                                          */
char *StrCpyRec(char *dest, const char *src, char *og_dest);

#include "recursion.h"

long Fibonacci(unsigned int n)
{
    unsigned int i = 0; 
    long old_sum = 0, sum = 1; 
    
    if (!n)
    {   
        return old_sum; 
    }

    for (i = 1; i < n; ++i)    
    {
        sum += old_sum; 
        old_sum = sum - old_sum; 
    }
    
    return sum; 
}

int Fib(unsigned int n)
{
     if (n <= 2)
     {
         return 1; 
     }
     
     return (Fib(n-1) + Fib(n-2));
}

size_t Strlen(const char *str)
{
    if (*str == '\0')
    {
        return 0; 
    }
    return (1 + Strlen(str + 1));
}

int Strcmp(const char *str1, const char *str2)
{
    if ((*str1 == '\0') || (*str1 != *str2))
    {
        return *str1 - *str2; 
    }

    return Strcmp(str1 + 1, str2 + 1); 
}

char *Strcpy(char *dest, const char *src)
{
    *dest = *src;
    
    if (*dest != '\0')
    {
        Strcpy(dest + 1, src + 1);
    }

    return dest; 
}

char *Strcat(char *dest, const char *src)
{
    if (*dest != '\0')
    {        
        Strcat(dest + 1, src);
    }
    else if (*src != '\0')
    {
            *dest = *src; 
            ++dest; 
            *dest = '\0';
            Strcat(dest , src + 1);
    }
    
    return dest; 
}

char *Strstr(const char *haystack, const char *needle)
{   
    if (*haystack == '\0')
    {
        return NULL; 
    }
    if (!strncmp(needle, haystack, strlen(needle)))
    {
        return (char*)haystack;
    }
    
    return (Strstr(haystack + 1, needle)); 
}

/* node_t *SLLFlipRec(node_t *head)
{
    assert (head);

    if (NULL == head)
    {
        return NULL; 
    }
    
    ReverseList(&head, head); 

    return head; 
}

static void ReverseList(node_t **head, node_t *node)
{
    if (node->next == NULL) 
    {
        *head = node;
        return; 
    }

    ReverseList(head, node->next);
    node->next->next = node;
    node->next = NULL;  
} 
 */

