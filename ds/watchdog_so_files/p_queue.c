/*******************************************************************************
* Programmer: Avihay Asraf
* pq.c
* File: pq code
* Date: 22/5/19
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */

#include "p_queue.h"
#include "sorted_list.h"
/*----------------------------------------------------------------------------*/
struct priority_queue
{
  slist_t *list;   
};

/*----------------------------------------------------------------------------*/
pq_t *PQCreate(int(*is_before)(const void* data, const void *param))
{
    pq_t *pq = (pq_t*)malloc(sizeof(pq_t));
    if (NULL == pq)
    {
        return NULL; 
    }
    pq->list = SortedListCreate(is_before);
    if (NULL == pq->list)
    {
        free(pq); 
        pq = NULL; 
        
        return NULL; 
    }
    
    return ((pq_t*)pq); 
}
/*----------------------------------------------------------------------------*/
void PQDestroy(pq_t *pq)
{
    if (NULL == pq)
    {
        return; 
    }
    
    SortedListDestroy((pq->list));
    pq->list = NULL; 
    free(pq);
    pq = NULL; 
}

/*----------------------------------------------------------------------------*/

int PQIsEmpty(const pq_t *pq)
{
    assert(pq);
    
    return SortedListIsEmpty(pq->list);
}

/*----------------------------------------------------------------------------*/

size_t PQSize(const pq_t *pq)
{
    assert(pq);
    
    return (SortedListCount(pq->list));
}

/*----------------------------------------------------------------------------*/

int PQEnqueue(pq_t *pq, const void* data)
{
    assert(pq);
    
    return (NULL == SortedListInsert(pq->list, data));
}

/*----------------------------------------------------------------------------*/
void *PQDequeue(pq_t *pq)
{
    assert(pq);
    
    return(SortedListPopBack(pq->list));
}
/*----------------------------------------------------------------------------*/
void *PQPeek(const pq_t *pq)
{
    assert(pq);
    
    return(SortedListGetData(SortedListPrev(
                                    SortedListEnd(pq->list))));   
}
/*----------------------------------------------------------------------------*/

void *PQRemove(pq_t *pq, int(*is_found)(const void* data, const void *param), 
                                                            const void *param)
{
    slist_iter_t iter = NULL; 
    void *data         = NULL;
     
    assert (pq);
    
    iter = SortedListFind(pq->list, is_found, (void*)param);
    if (iter != NULL)
    {
       data = SortedListGetData(iter); 
       SortedListErase(iter);   
    }
  
    return (data);
}
/****************************************************************************/

