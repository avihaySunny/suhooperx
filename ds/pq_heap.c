/*******************************************************************************
* Programmer: Avihay Asraf
* pq_heap.c
* File: pq_heap code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */

#include "heap.h" 
#include "pq_heap.h"

typedef struct placeholder
{
    void *data; 
    void **location; 
    int (*is_match)(const void *data, const void *param);

} placer_t;

static void UpdateBundle(placer_t *bundle, void *data, int(*is_found)(const void* data, const void *param));
static int WrapperIsMatch(const void *data, const void *param);

struct pq 
{
    heap_t *heap; 
};

pq_t *PQCreate(int(*is_before)(const void* data, const void *param))
{
    pq_t *pq = (pq_t*)malloc(sizeof(pq_t)); 
    if (NULL == pq)
    {
        return NULL; 
    }

    pq->heap = HEAPCreate(is_before); 
    if (NULL == pq->heap)
    {
        free(pq);
        return NULL; 
    }

    return pq; 
}

void PQDestroy(pq_t *pq)
{
    assert(pq);
    HEAPDestroy(pq->heap); 
    free (pq);
}

int PQEnqueue(pq_t *pq, const void *data)
{
    assert(pq); 
    assert(data);

    return(HEAPInsert(pq->heap, (void*)data));
} 

void *PQDequeue(pq_t *pq)
{
    void *head_data = NULL; 
    assert(pq);
    
    head_data = HEAPPeek(pq->heap); 
    HEAPPop(pq->heap);

    return head_data; 
}

void *PQPeek(const pq_t *pq)
{
    assert(pq); 
    return (HEAPPeek(pq->heap));
}

int PQIsEmpty(const pq_t *pq)
{
    assert(pq);
    return (HEAPIsEmpty(pq->heap));
}

size_t PQSize(const pq_t *pq)
{
    assert(pq); 
    return (HEAPSize(pq->heap));
}

void *PQRemove(pq_t *pq, int(*is_found)(const void* data, const void *param),  const void *param)
{
    placer_t bundle = {NULL, NULL, NULL}; 
    UpdateBundle(&bundle, (void*)param, is_found);
    HEAPRemove(pq->heap, &bundle, WrapperIsMatch);
    
    return bundle.location; 
}

static int WrapperIsMatch(const void *param, const void *data)
{   
    placer_t *bundle = (placer_t*)param; 
    
    if (bundle->is_match(data, bundle->data))
    {
        bundle->location = (void*)data; 
        return 1; 
    }
    
    return 0; 
}

static void UpdateBundle(placer_t *bundle, void *data, int(*is_found)(const void* data, const void *param))
{
    bundle->data = data; 
    bundle->is_match = is_found;
}