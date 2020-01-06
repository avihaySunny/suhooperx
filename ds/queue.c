/*******************************************************************************
* Programmer: Avihay Asraf
* queue.c
* File: queue code
* Date: ה' מאי 16 09:59:10 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */ 
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */ 

#include "./include/queue.h"
#include "./include/sll.h"


struct queue
{
    node_t *tail; 
    node_t *head; /*also acts as stub*/  
}; 

queue_t *QCreate(void)
{
    queue_t *q = (queue_t*)malloc(sizeof(queue_t)); 
    if (NULL == q)
    {
        return NULL; 
    }
    
    q->tail = SLLCreateNode(NULL, NULL); /*create stub*/
    if (NULL == q->tail)
    {
        free(q);
        q = NULL; 
        return NULL; 
    }
    
    q->head = q->tail; 
    
    return (q);    
}

int QIsEmpty(const queue_t *q)
{
    assert(q); 
    
    return (q->head == q->tail); 
}

void QDestroy(queue_t *q)
{
    SLLFreeAll(q->head);
    q->head = NULL;
    q->tail = NULL;  
    free(q);
    q = NULL; 
}

int QEnqueue(queue_t *q, void *data)
{
    node_t *tmp = NULL; 
    
    assert(q);
    assert(data);
    
    tmp = SLLCreateNode(data, NULL);
    if (tmp == NULL) 
    {
        return (1);
    }
    
    q->tail = SLLInsertAfter(q->tail, tmp);
    
    return (0);      
}

void *QDequeue(queue_t *q)
{   
    void *data      = NULL; 
    node_t *removed = NULL; 
    
    assert(q);
    
    removed = q->head->next;
    data    = removed->data; 
     
    if (removed == q->tail) /*if only one element   */
    {
        q->tail = q->head;  /*sets to be empty again*/  
        removed = NULL; 
        free(removed);          
    
        return (data);
    }
    
    removed = SLLRemoveAfter(q->head); 
    free(removed);
    removed = NULL; 
    
    return (data);   
}

size_t QCount(const queue_t *q)
{
    assert(q); 
    
    return (QIsEmpty(q) ? (0) : (SLLCount(q->head)- 1));
}

void *QPeek(const queue_t *q)
{
    assert(q); 
    
    return(q->head->next->data);
}

queue_t *QAppend(queue_t *dest, queue_t *src)
{
    assert(dest);
    dest->tail->next = src->head->next;  
    dest->tail       = src->tail; 
    src->head->next  = NULL;  
    QDestroy(src);
    src = NULL;   
    
    return (dest);
}

