/*******************************************************************************
* Programmer: Avihay Asraf
* heap.c
* File: heap code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#include "heap.h"
#include "vector.h"

#define DEF_ELEMET_SIZE (50)
#define PARENT(x) ((x - 1) / 2 )
#define LEFT(x) (2 * x + 1)
#define RIGHT(x) (2 * x + 2)

static void SwapData(void **dataA, void **dataB);
static void HeapifyDown(heap_t *heap, size_t indx);
static size_t FindMax(heap_t *heap, size_t lchild, size_t rchild);
static void HeapifyUp(heap_t *heap, size_t curr_indx);
/*---------------------------------------------------------------------------- */
struct heap 
{
    vect_t *vec; 
    int (*is_bigger)(const void*, const void*);
};
/* ---------------------------------------------------------------------------- */
heap_t *HEAPCreate(is_before_t is_before)
{
    heap_t *heap = (heap_t*)malloc(sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL; 
    }    

    heap->vec = VecCreate(sizeof(size_t), DEF_ELEMET_SIZE);
    if (NULL == heap->vec)
    {
        free(heap); 
        return NULL;
    }

    heap->is_bigger = is_before; 
    return heap; 
}
/* ---------------------------------------------------------------------------- */
void HEAPDestroy(heap_t *heap)
{
    assert(heap);

    VecDestroy(heap->vec); 
    free(heap); 
}
/* ---------------------------------------------------------------------------- */
size_t HEAPSize(const heap_t *heap)
{
    assert(heap);
    
    return VecGetSize(heap->vec);
}

int HEAPIsEmpty(const heap_t *heap)
{
    assert(heap); 

    return (0 == VecGetSize(heap->vec)); 
}

void *HEAPPeek(const heap_t *heap)
{
    assert(heap);

    return *(void**)VecGetItemAddress(heap->vec, 0);
}

static void SwapData(void **dataA, void **dataB)
{
    void *tmp = NULL; 
    assert(dataA && dataB);

    tmp = *dataA;
    *dataA = *dataB; 
    *dataB = tmp; 
}
 
void HEAPPop(heap_t *heap)
{
    size_t vec_size = 0;
    void **top_data = NULL; 
    void **replacement = NULL; 
    
    assert(heap);
    
    vec_size = VecGetSize(heap->vec);
    
    top_data    = (void**)VecGetItemAddress(heap->vec, 0); 
    replacement = (void**)VecGetItemAddress(heap->vec, vec_size - 1);    
    SwapData(replacement, top_data); 
    VecPop(heap->vec);
    HeapifyDown(heap, 0);

} 

int HEAPInsert(heap_t *heap, void *data)
{
    int status = 0;
    assert (heap); 

    status = VecPush(heap->vec, &data);
    HeapifyUp(heap, VecGetSize(heap->vec) - 1);

    return status; 
}

static void HeapifyUp(heap_t *heap, size_t curr_indx)
{
    void **curr_data_ptr = NULL; 
    void **parent_data_ptr = NULL; 

    assert(heap);

    if (0 == curr_indx)
    {
        return; 
    }
    else
    {
        curr_data_ptr = (void**)VecGetItemAddress(heap->vec, curr_indx);
        parent_data_ptr = (void**)VecGetItemAddress(heap->vec, PARENT(curr_indx));

        if(heap->is_bigger(*curr_data_ptr, *parent_data_ptr))
        {
            SwapData(curr_data_ptr, parent_data_ptr);
            HeapifyUp(heap, PARENT(curr_indx));
        }
    }  
}

void HEAPRemove(heap_t *heap, void *data, is_match_t match_func)
{ 
    size_t found_indx = 0, i  = 0; 
    void **found_data_ptr = NULL; 
    void **last_item_ptr  = NULL; 
    
    assert(heap && data);

    for (i = 0; i < VecGetSize(heap->vec); ++i)
    {
        if(match_func(data, *(void**)VecGetItemAddress(heap->vec, i)))
        {
            found_indx = i;
                /* prepare for swapping  */
            found_data_ptr = (void**)VecGetItemAddress(heap->vec, found_indx); 
            last_item_ptr = (void**)VecGetItemAddress(heap->vec, VecGetSize(heap->vec) - 1); 
            SwapData(found_data_ptr, last_item_ptr);
            VecPop(heap->vec);

                /* maintaining heap */
            HeapifyUp(heap, found_indx);
            HeapifyDown(heap, found_indx);
            break;
        }
    } 
}

static void HeapifyDown(heap_t *heap, size_t curr_indx)
{
    size_t lchild = LEFT(curr_indx); 
    size_t rchild = RIGHT(curr_indx);
    size_t nxt_child = 0; 
    size_t vec_size = 0; 
    
    void **curr_data_ptr = NULL;
    void **nxt_data_ptr = NULL;
    
    assert(heap); 

    vec_size = VecGetSize(heap->vec);
    (vec_size == 0) ? (vec_size) : (--vec_size);  

    if(lchild > vec_size)
    {
        return; 
    }
    if(rchild > vec_size)
    {
        nxt_child = lchild; 
    }
    else
    {
        nxt_child = FindMax(heap, lchild, rchild); 
    }
    
    nxt_data_ptr = (void**)VecGetItemAddress(heap->vec, nxt_child);
    curr_data_ptr = (void**)VecGetItemAddress(heap->vec, curr_indx);
    
    if (heap->is_bigger(*nxt_data_ptr, *curr_data_ptr))
    {
        SwapData(nxt_data_ptr, curr_data_ptr);
        HeapifyDown(heap, nxt_child);
    }
}

static size_t FindMax(heap_t *heap, size_t lchild, size_t rchild)
{
    void **rchild_data_ptr = NULL; 
    void **lchild_data_ptr = NULL; 

    assert(heap);

    rchild_data_ptr = (void**)VecGetItemAddress(heap->vec, rchild);
    lchild_data_ptr = (void**)VecGetItemAddress(heap->vec, lchild);

    return (heap->is_bigger (*rchild_data_ptr, *lchild_data_ptr) ? (rchild) : (lchild));
}
