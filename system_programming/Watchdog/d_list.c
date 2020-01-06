/*******************************************************************************
* Programmer: Avihay Asraf
* dll.c
* File: dll code
* Date: 20/5/19
* Version : 2 
*******************************************************************************/
#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /*  malloc realloc                          */

#include "d_list.h"

#define UNUSED(a)   ((void)(a))  /* for unusued variables   */

/*--------------------Internal Functions-----------------------------------------------*/
dlist_iter_t DLLCreateNode(const void *data);   /*Creates Doubly node for the list     */
static int DLCounter(void *data, void *param);  /* Count Function for use with ForEach */
static void DestroyNodes(dlist_t *list);        /*Part of Destructor nodes             */
static int DLCounter(void *data, void *param);  /*Counter action function              */ 
static void DLEraseNode(dlist_iter_t to_erase); 

/*-------------------------------------------------------------------------------------*/
struct dll_node
{
    void *data;
    struct dll_node *next; 
    struct dll_node *prev;  
};

struct dll_dlist
{
    struct dll_node start; 
    struct dll_node end; 
};

dlist_iter_t DLCreateNode(const void *data)
{
    dlist_iter_t dnode = (dlist_iter_t)malloc(sizeof(struct dll_node)); 
    
    if (NULL == dnode)
    {
        return NULL; 
    }
    
    dnode->next = NULL;
    dnode->prev = NULL;
    dnode->data = (void*)data; 
    
    return dnode; 
}

dlist_t *DLCreate(void)
{
    dlist_t *dlist = (dlist_t*)malloc(sizeof(dlist_t));
    if(NULL == dlist)
    {
        return NULL; 
    }     
    
    dlist->start.next = &dlist->end; 
    dlist->start.prev = NULL; 
    dlist->start.data = NULL;
    dlist->end.prev   = &dlist->start; 
    dlist->end.next   = NULL; 
    dlist->end.data   = NULL;
    
    return (dlist);
}

void DLDestroy(dlist_t *dlist)
{
    
    if (NULL == dlist)
    {
        return; 
    }
    
    DestroyNodes(dlist);
    free(dlist); 
    dlist = NULL; 
}

int DLIsEmpty(const dlist_t *dlist)
{
    assert(dlist);
    
    return (dlist->start.next == &dlist->end); 
}

dlist_iter_t DLErase(dlist_iter_t to_erase)
{
    dlist_iter_t next = NULL; 
    
    if (to_erase == NULL)
    {
        return NULL;
    }
    
    to_erase->prev->next    = to_erase->next; 
    to_erase->next->prev    = to_erase->prev;
    next                    = DLNext(to_erase); 
    DLEraseNode(to_erase); 
    to_erase                = NULL; 
    
    return next;  
}

static void DLEraseNode(dlist_iter_t to_erase)
{
    to_erase->prev = NULL; 
    to_erase->next = NULL;
    free(to_erase);
    to_erase = NULL;   
}

dlist_iter_t DLInsertBefore(dlist_iter_t where, const void *data)
{
    dlist_iter_t dnode = NULL;
    
    assert(where); 
    
    dnode = DLCreateNode(data);
    if(NULL == dnode)
    {
        return (NULL); 
    } 
    
    dnode->next       = where; 
    dnode->prev       = DLPrev(where);  
    where->prev->next = dnode;
    where->prev       = dnode; 
    
    return (DLPrev(where));
}

dlist_iter_t DLBegin(const dlist_t *dlist)
{
    assert(dlist);
    
    return (dlist->start.next); 
}

dlist_iter_t DLEnd(const dlist_t *dlist)
{
    assert(dlist); 
    
    return ((dlist_iter_t)&dlist->end);
}

dlist_iter_t DLNext(const dlist_iter_t iter)
{
    assert(iter);
    
    return(iter->next);
}

dlist_iter_t DLPrev(const dlist_iter_t iter)
{
    assert(iter);
    
    return(iter->prev);
}

int DLIsSameIterator(const dlist_iter_t iter1, const dlist_iter_t iter2)
{
    return (iter1 == iter2);
}

int DLIsBadIterator(const dlist_t *dlist, const dlist_iter_t iter)
{  
    return ((iter == DLEnd(dlist)) || (iter == NULL));
}

dlist_iter_t DLPushFront(dlist_t *dlist, const void *data)
{
    return (DLInsertBefore(DLBegin(dlist), data));
}

dlist_iter_t DLPushBack(dlist_t *dlist, const void *data)
{
    return (DLInsertBefore(DLEnd(dlist), data));
}

void DLPopFront(dlist_t *dlist)
{
    DLErase(DLBegin(dlist)); 
}

void DLPopBack(dlist_t *dlist)
{
    DLErase(DLPrev(DLEnd(dlist))); 
}

void *DLGetData(const dlist_iter_t iter)
{
    assert(iter);
    
    return (iter->data);
}

int DLForEach(dlist_t *dlist,
              int(*action_func)(void *data, void *param),
              void *param, dlist_iter_t *failed_iter)
{   
    int status = 0;     
    dlist_iter_t runner = NULL; 
    
    assert(dlist); 
    runner = DLBegin(dlist);  
    while (DLEnd(dlist) != runner)
    {
        status = action_func(DLGetData(runner), param); 
        if (0 != status)
        {
            *failed_iter = runner; 
            return status; 
        }
        
        runner = DLNext(runner);
    }
    
    return 0; 
}

size_t DLCount(const dlist_t *dlist)
{
    size_t count = 0; 
    void *stub = NULL; 
    
    assert(dlist);
    DLForEach((dlist_t*) dlist, DLCounter, &count, stub);
  
    return (count);
}

static int DLCounter(void *data, void *param)
{
    UNUSED(data); 
    ++*(size_t*)param; 
    
    return (0);
}

static void DestroyNodes(dlist_t *list)
{
    dlist_iter_t runner = NULL; 
    assert (list); 
    
    runner = DLBegin(list); 
    while ((DLEnd(list) != runner) && (runner != NULL))
    {
        runner = DLErase(runner); 
    }
}

dlist_iter_t DLFind(dlist_t *dlist,
                  int(*is_match)(const void *data, const void *param),
                  const void *param)
{
    dlist_iter_t found = NULL;
    DLForEach((dlist_t*)dlist, (int(*)(void*, void*))is_match,(void *)param, &found); 
    
    return (found);     
}

dlist_iter_t DLSpliceBefore(dlist_iter_t dest, dlist_iter_t src_from, dlist_iter_t src_to) 
{
     dlist_iter_t temp = NULL;

    assert(dest);
    
    temp = src_from->prev;
    src_from->prev = dest->prev; 
    dest->prev->next = src_from;
    dest->prev = src_to->prev; 
    src_to->prev->next = dest;  
    temp->next = src_to;
    src_to->prev = temp;
       
    return (DLPrev(dest));  

}
void DLPrint(const dlist_t *list)
{
    dlist_iter_t stub = NULL; 
    assert(list); 
    DLForEach((dlist_t*)list, DLPrinter, stub, &stub);
}

int DLPrinter(void *data, void *param)
{
    printf("%d\n",*(int*)data);
    UNUSED(param);
    
    return (0);     
} 

