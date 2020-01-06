#include <stdio.h> 
#include <assert.h>
#include <stdlib.h>

#include "./include/queue.h"

int EnqInt(queue_t *q , int data)
{
    assert(q);

    return QEnqueue(q, (void*)(size_t)data); 
}

int DeqInt(queue_t *q)
{   
    void *data_ptr = NULL; 

    assert(q); 
    
    data_ptr = QDequeue(q); 

    return (*(int*)&data_ptr);
}

int QPeekInt(queue_t *q)
{
    void *data_ptr = NULL; 

    assert(q); 

    data_ptr = QPeek(q);

    return (*(int*)&data_ptr);
}

int QIsEmptyInt(queue_t *q)
{
    assert(q);
    return QIsEmpty(q);
}

size_t QCountInt(queue_t *q)
{
    return QCount(q);
}

int main (void)
{
    queue_t *q = QCreate(); 
    int arr[10] = {0}; 
    int i = 0; 
    
    printf("is empty:%d\n", QIsEmpty(q));

    for(i = 1; i < 10; ++i)
    {
        arr[i] = i;
        EnqInt(q, arr[i]);
    }

    printf("Is Empty %d\n", QIsEmpty(q));
    printf("Count : %ld\n", QCountInt(q));
    
    for (i = 1; i < 10; ++i)
    {
        printf("%d\n", DeqInt(q));
    }

    return (EXIT_SUCCESS);
}

