/*******************************************************************************
* Programmer: Avihay Asraf
* sll.c
* File: sll code
* Date: 16/5/19
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <strings.h>        /*  strcasecmp                              */

#include "sll.h"
/*----------------------------------------------------------------------------*/
static int SLLCounter(void *data, void *param); 

node_t *SLLCreateNode(const void *data, node_t *next) 
{
    node_t *node = (node_t*)malloc(sizeof(node_t)); 
    if (NULL == node)
    {
        return (NULL); 
    }
    
    node-> data = (void*)data; 
    node-> next = next;
    
    return (node); 
}

node_t *SLLInsertAfter(node_t *where, node_t *node)
{
    assert(where);
    assert(node);
    
    node->next = where->next;
    where->next = node;
      
    return (node);
}

node_t *SLLInsertBefore(node_t *where, node_t *node)
{
    void *data = NULL; 
    
    assert(where);
    assert(node);
    
    SLLInsertAfter(where, node); 
    data = where->data; 
    where->data = node->data; 
    node->data = data;
    
    return (node); 
}

void SLLFreeAll(node_t *head)
{
    node_t *tmp_node= NULL;  
    
    while(NULL != head)
    {
        tmp_node = head; 
        head = head->next; 
        SLLFreeNode(tmp_node);
    }
}

void SLLFreeNode(node_t *node)
{
    if (NULL == node)
    {
        return; 
    }
    
    node->data = NULL; 
    node->next = NULL; 
    free(node);    
}

node_t *SLLRemoveAfter(node_t *node)
{
    node_t *tmp = NULL;    
    assert(node); 
    
    if (NULL == node->next)
    {
       return NULL;  
    }
    
    tmp = node->next; 
    node->next = node->next->next; 
    tmp->next = NULL;
    
    return (tmp);
}

node_t *SLLRemoveCurrent(node_t *node)
{
    void *temp = NULL;

    assert(node);
    
    temp = node->data;
    node->data = node->next->data;
    node->next->data = temp;
    
    return (SLLRemoveAfter(node));
}

node_t *SLLFlip(node_t *head)
{
    node_t *tmp_next = NULL; 
    node_t *tmp_previous = NULL; 
 
    while (NULL != head)
    {
        tmp_next     = head ->next; 
        head->next   = tmp_previous; 
        tmp_previous = head; 
        head         = tmp_next;        
    } 
    
    return (tmp_previous);
}

int SLLHasLoop(const node_t *head)
{
    node_t *runner = NULL; 
    node_t *fast_runner = NULL; 
        
    if (NULL == head)
    {
        return 0; 
    } 
    
    runner      = (node_t*)head;
    fast_runner = (node_t*)head->next;  
    
    while ((runner != fast_runner) && (NULL != fast_runner)) 
    {
        if (fast_runner->next == NULL)
        {
            return (0);
        }
        
        fast_runner = fast_runner-> next->next; 
        runner      = runner-> next;    
    }
    
    return (1);
}

int SLLForEach(node_t *head, int(*action)(void *data, void *param), 
               void *param, node_t **failed_node)
{   
    int err = 0;     
    
    while (NULL != head)
    {
        err = action(head->data, param); 
        if (0 != err)
        {
            *failed_node = head; 
            return err; 
        }
        
        head = head->next;
    }
    
    return 0; 
}

node_t *SLLFind(const node_t *head, int(*ismatch)(const void *data,
                const void *param), const void *param)
{
    node_t *found = NULL;
    node_t *new_head = (node_t*)head;  
    
    SLLForEach(new_head, (int(*)(void*, void*))ismatch,(void *)param, &found); 
    
    return (found);     
}

size_t SLLCount(const node_t *head)
{
    size_t count = 0; 
    void *stub = NULL; 
    
    assert(head);
    SLLForEach((node_t*)head, SLLCounter, &count, stub);
  
    return (count);
}

static int SLLCounter(void *data, void *param)
{
    UNUSED(data); 
    ++*(size_t*)param; 
    
    return (0);
}

node_t *SLLFindIntersection(const node_t *head1, const node_t *head2)
{
    size_t size_a = 0;
    size_t size_b = 0; 
    size_t i      = 0; 
    
    node_t *runner_a = NULL; 
    node_t *runner_b = NULL; 
    
    assert(head1);
    assert(head2); 
    
    runner_a = (node_t*)head1; 
    runner_b = (node_t*)head2; 
    size_a = SLLCount(head1); 
    size_b = SLLCount(head2);
    
    if (size_a > size_b)
    {
        for(i = 0; i < size_a - size_b; ++i, runner_a = runner_a->next);
    }
    else
    {
         for(i = 0; i < size_b - size_a; ++i, runner_b = runner_b->next);
    }
    
    while (runner_a != runner_b)
    {
        runner_a = runner_a-> next; 
        runner_b = runner_b-> next; 
    }
    
    return(runner_a); 
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
}  */

node_t  *FlipRec (node_t *head) 
{
    node_t *curr_head = NULL; 
    
    if(head->next == NULL)
    {
        return head;
    }

    else 
    {
        curr_head = FlipRec(head->next);
        head->next->next = head;
        head->next = NULL;
        
        return curr_head;
    }
}

