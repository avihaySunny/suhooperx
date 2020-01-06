/*******************************************************************************
* Programmer: Avihay Asraf
* vector.c
* File: vector code
* Date: ג' מאי  7 15:29:54 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */

#include "vector.h"

#define GROW_FACTOR (2)
#define SHRINK_FACTOR (4)
DBG(static void GenericPrintElement(void *to_print);)

struct dynamic_vector 
{
    void *head; 
    size_t element_size; 
    size_t n_elements; 
    size_t max_elements; 
};

vect_t *VecCreate(size_t element_size, size_t max_elements)
{
    vect_t *dv = (vect_t*)malloc(sizeof(vect_t)); 
    
    if ((NULL == dv) || (0 == element_size))
    {
        return (NULL); 
    }
    
    dv->head = malloc(max_elements * element_size); 
    if (NULL == dv->head)
    {
        free(dv);
        dv = NULL; 
        return (NULL); 
    }

    dv->element_size  = element_size; 
    dv->n_elements    = 0;
    dv-> max_elements = max_elements;  
    
    return (dv); 
}

void VecDestroy(vect_t *dv)
{
    if(dv == NULL)
    {
        return; 
    }
    
    free((void*)dv->head); 
    dv->head = NULL;
    free(dv); 
    dv = NULL;  
}

void *VecGetItemAddress(const vect_t *dv, size_t index)
{
    assert(dv); 
    
    return ((char*)dv->head + (index * dv->element_size));  
}

ssize_t VecPush(vect_t *dv, const void *data)
{   
    assert(dv);
    assert(data);
    if(dv->max_elements == dv->n_elements) /* vector is full? */
    {
       /*resizing vector by grow factor */
       if (-1 == VecReserve(dv, (dv->max_elements * GROW_FACTOR) - dv->max_elements))
       {
           return (-1);
       }
    }

    memcpy((char*)dv->head + (dv->n_elements * dv->element_size),
                                                     data, dv->element_size);
    dv->n_elements = dv->n_elements + 1; 
    
    return (dv->n_elements - 1);      
}

ssize_t VecPop(vect_t *dv)
{    
    assert(dv); 
    if(!VecGetSize(dv))                                         /*if empty   */
    {
        return (-1);
    } 
    
    if(dv->n_elements <= (dv->max_elements / SHRINK_FACTOR )) /*less than 25% so shrink*/
    {
        
        if(-1 == VecReserve(dv, (dv->max_elements / GROW_FACTOR) - dv->max_elements))
        {
            return (-1);
        }
    }
    
    --dv->n_elements;
    
    return (0); 
}

ssize_t VecReserve(vect_t *dv, size_t n_elements)
{
    void *temp_head = NULL;
    
    assert(dv);
     
    temp_head = dv->head; 
    temp_head = realloc(temp_head, dv->element_size * (dv->max_elements + n_elements));
    if (NULL == temp_head)
    {
        return (-1);
    }
    
    dv->head = temp_head;
    dv->max_elements = dv->max_elements + n_elements; 
    
    return(0);
}

size_t VecGetCapacity(const vect_t *dv)
{
    assert(dv); 
    
    return (dv->max_elements);
}

size_t VecGetSize(const vect_t *dv)
{
    assert(dv); 
    return (dv->n_elements);
}

#ifndef NDEBUG /*for debug mode use*/

void VecPrint(const vect_t *dv, void(print_element(void*)), size_t n_elements)
{
    size_t i = 0; 
    char msg[60] = "Printing with given function";
    assert(dv); 
    
    puts(RED"Print MetaData:"RESET); 
    printf("Size Of dynamic array %ld\n", VecGetCapacity(dv)); 
    printf("Number Of Elements in array  %ld\n", dv->n_elements ); 
    printf("Size Of each Element %ld bytes\n", dv-> element_size); 
    
    if (NULL == print_element)              /*Default option*/
    {
        print_element = GenericPrintElement; 
        strcpy(msg, "Printing With GENERIC print function");
    }
   
    printf(YELLOW"%s\n"RESET, msg); 
    for (i = 0; i < n_elements; ++i)
    {
        print_element(VecGetItemAddress(dv,i));
    }
}

static void GenericPrintElement(void *to_print)
{
    assert(to_print); 
    printf("%d\n", *(int*)to_print);
}

#endif  /*end of debug */
