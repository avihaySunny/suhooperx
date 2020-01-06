/*******************************************************************************
* Programmer: Avihay Asraf
* heap_sort.c
* File: heap_sort code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */
#include "heap_sort.h"

static void MaxHeapify(void *base, size_t indx, size_t heap_size, size_t el_size, int (*is_before)(const void *, const void*));
static void BuildHeap(void *base, size_t heap_size, size_t el_size, 
                        int (*is_before)(const void *, const void*));
static void *IndxData(void *base, size_t indx, size_t el_size);
static void HeapSwap(size_t element_size, const void *data1, const void *data2);


void HeapSort(void *base, size_t num_el, size_t el_size, int (*is_before)(const void *, const void*))
{
    int i = 0; 

    assert(base); 

    BuildHeap(base, num_el, el_size, is_before);
    for (i = (int)num_el - 1; i > 0; --i)
    {
        HeapSwap(el_size, IndxData(base ,0, el_size), IndxData(base, i, el_size)); 
        MaxHeapify(base, 0, i - 1, el_size, is_before);
    } 

}

static void BuildHeap(void *base, size_t heap_size, size_t el_size, 
                        int (*is_before)(const void *, const void*))
{
    int i = 0; ; 
    
    assert(base);
    
    for (i = (int)heap_size / 2; i >= 0; --i)
    {
        MaxHeapify(base, i, heap_size - 1, el_size, is_before);
    }
}

static void MaxHeapify(void *base, size_t indx, size_t heap_size, 
                size_t el_size, int (*is_before)(const void *, const void*))
{
    size_t nxt_indx = 0; 

    assert(base);

    if (indx * 2 + 1 > heap_size)
    {
        return; 
    }
    if (indx * 2 + 2 > heap_size)
    {
        nxt_indx = indx * 2 + 1; 
    }
    else
    {   /* Finds the max element of two leaves */
        if(is_before(IndxData(base, 2 * indx + 1, el_size), 
                     IndxData(base, 2 * indx + 2, el_size)))
        {
            nxt_indx = 2 * indx + 1; 
        }
        else
        {
            nxt_indx = 2 * indx + 2; 
        }
    }

    if (is_before(IndxData(base ,nxt_indx, el_size), 
                     IndxData(base, indx, el_size)))
    {
        HeapSwap(el_size ,IndxData(base ,nxt_indx, el_size), IndxData(base, indx, el_size));
        MaxHeapify(base, nxt_indx, heap_size, el_size, is_before);
    }
}

static void *IndxData(void *base, size_t indx, size_t el_size)
{
    assert(base); 
 
    return (void*)((size_t)base + indx * el_size); 
}

static void HeapSwap(size_t element_size, const void *data1, const void *data2)
{
    size_t i = 0;
    
    assert (data1); 
    assert (data2); 

    for (i = 0; (i < element_size) && (data1 != data2); ++i)
    {
        *((char*)data1 + i) ^= *((char*)data2 + i);
        *((char*)data2 + i) ^= *((char*)data1 + i);
        *((char*)data1 + i) ^= *((char*)data2 + i);
    }
}




