/*******************************************************************************
* Programmer: Avihay Asraf
* sorted.c
* File: sorted code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */

#include "sorted_list.h"
#include "d_list.h"

struct sorted_list 
{
    int (*is_before)(const void*, const void*);
    dlist_t *list;        
};
/*-----------------------------------------------------------------------------*/
slist_t *SortedListCreate(int(*is_before)(const void *left, const void *right))
{
    slist_t *slist = (slist_t*)malloc(sizeof(slist_t));
    if (NULL == slist) 
    {
        return NULL; 
    }
    
    slist->list = DLCreate();
    if (NULL ==  slist->list)
    {
        free(slist);
        slist = NULL; 
    }
    
    slist->is_before = is_before; 
    
    return slist; 
}
/*-----------------------------------------------------------------------------*/

void SortedListDestroy(slist_t *slist)
{
    if (NULL == slist)
    {
        return; 
    }
    
    DLDestroy(slist->list);
    slist->list      = NULL;
    slist->is_before = NULL; 
    free (slist); 
    slist = NULL; 
}

/*-----------------------------------------------------------------------------*/

size_t SortedListCount(const slist_t *slist)
{
    assert (slist); 
    
    return DLCount(slist->list); 
}

/*-----------------------------------------------------------------------------*/

slist_iter_t SortedListInsert(slist_t *slist, const void *data)
{
    dlist_iter_t iter = NULL; 
    assert (data);
    DLForEach(slist->list, (int(*)(void *, void *))slist->is_before,
                                                      (void*)data, &iter);
    if (NULL == iter)
    {
        iter = DLEnd(slist->list); 
    }
   
    return (DLInsertBefore(iter, data));
}

/*-----------------------------------------------------------------------------*/

slist_iter_t SortedListErase(slist_iter_t iter)
{
    assert(iter);
    
    return (DLErase(iter));
}

/*-----------------------------------------------------------------------------*/

int SortedListForEach(slist_t *slist,
               	  int(*action_func)(void *data, void *param),
                  void *param, slist_iter_t *failed_iter)
{
    assert(slist);
    
    return(DLForEach(slist->list, action_func, param, *failed_iter));
}

/*-----------------------------------------------------------------------------*/

slist_iter_t  SortedListFind(slist_t *slist,
                    int(*is_match)(const void *data, const void *param),
                    const void *param)
{
     assert(slist);
  
     return (DLFind(slist->list, is_match, param));  
}                    
/*-----------------------------------------------------------------------------*/

int SortedListIsEmpty(const slist_t *slist)
{
    assert (slist); 
   
    return (DLIsEmpty(slist->list));
}

/*-----------------------------------------------------------------------------*/

slist_iter_t SortedListBegin(const slist_t *slist)
{
    assert (slist); 
    
    return(DLBegin(slist->list));
}

/*-----------------------------------------------------------------------------*/

slist_iter_t SortedListEnd(const slist_t *slist)
{
    assert (slist); 
    
    return (DLEnd(slist->list));
}

/*-----------------------------------------------------------------------------*/

slist_iter_t SortedListNext(const slist_iter_t iter)
{
    assert (iter); 
    
    return (DLNext(iter));
}

/*-----------------------------------------------------------------------------*/

slist_iter_t SortedListPrev(const slist_iter_t iter)
{
    assert (iter); 
    
    return (DLPrev(iter));    
}

/*-----------------------------------------------------------------------------*/

void *SortedListPopFront(slist_t *slist)
{
    void *data = NULL;
    
    assert(slist); 
    
    data = DLGetData(DLBegin(slist->list)); 
    DLPopFront(slist->list);
    
    return (data);
}  

/*-----------------------------------------------------------------------------*/

void *SortedListPopBack(slist_t *slist) 
{
    void *data = NULL;
    
    assert(slist); 
     
    data = DLGetData(DLPrev(DLEnd(slist->list))); 
    DLPopBack(slist->list);
    
    return (data);
} 

/*-----------------------------------------------------------------------------*/

int SortedListIsSameIterator(const slist_iter_t iter1,
 							 const slist_iter_t iter2)
{
    return (iter1 == iter2);
}

int SortedListIsBadIterator(const slist_t *slist, const slist_iter_t iter)
{
    return(DLIsBadIterator(slist->list, iter));
}

/*-----------------------------------------------------------------------------*/

void *SortedListGetData(const slist_iter_t iter)
{
    assert(iter); 
    
    return(DLGetData(iter)); 
}

/*-----------------------------------------------------------------------------*/
slist_t *SortedListMerge(slist_t *dest, slist_t *src)
{
    dlist_iter_t dest_runner = NULL; 
    dlist_iter_t src_from    = NULL;
    dlist_iter_t src_to      = NULL;  
    dlist_iter_t dest_end    = NULL; 
    dlist_iter_t src_end     = NULL; 
    
    assert(dest); 
    assert(src); 
    
    dest_runner = DLBegin(dest->list); 
    dest_end    = DLEnd(dest->list);
    
    src_from    = DLBegin(src->list); 
    src_to      = DLBegin(src->list); 
    src_end     = DLEnd(src->list);
    
    while ((dest_end != dest_runner) && (src_end != src_to))    /*none of lists are at end*/
    {                                                           /*is src data > dest data */
       if ((dest->is_before(DLGetData(src_to), DLGetData(dest_runner)))) 
       {    
           dest_runner = DLNext(dest_runner);
           
           while ((src_end     != src_to)       &&
                  (dest_runner != dest_end)     && 
                  (dest->is_before(DLGetData(dest_runner),DLGetData(src_to))))
                                                            
            {   
                src_to = DLNext(src_to);
            }
            
            DLSpliceBefore(dest_runner, src_from, src_to);
            src_from = src_to;      
        } 
        else 
        {                                                   /*is dest data > src data ? */ 
            while ((src_end     != src_to)       &&
                   (dest_runner != dest_end)     &&
                   dest->is_before(DLGetData(dest_runner), DLGetData(src_to)))
            {
                src_to = DLNext(src_to);
            }
            
            DLSpliceBefore(dest_runner, src_from, src_to);
            src_from = src_to; 
            dest_runner = DLNext(dest_runner);
        }            
    } 
    
    if (!SortedListIsEmpty(src))
    {
        DLSpliceBefore(dest_runner, src_from, src_end);
    }
    
    return dest;
}

/*-----------------------------------------------------------------------------*/


void SortedListPrint(slist_t *slist)
{
    slist_iter_t head = NULL;
    
    assert(slist);
    
    head = SortedListBegin(slist);
    
    while (SortedListEnd(slist) != head)
    {
        printf("%d\n",*(int*)SortedListGetData(head));
        head = SortedListNext(head);
    }
    
    puts("");
}

