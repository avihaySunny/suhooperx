#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>

#include "../ds/include/d_list.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 

void *Consumer(void *arg);
void *Producer(void *arg); 

int main (void)
{   
    pthread_t consumer, producer;
    int products_capacity = 0; 

    dlist_t *list = DLCreate(); 
    DLPushFront(list, &products_capacity);
    
    pthread_create(&producer, NULL, &Consumer, list);
    pthread_create(&consumer, NULL, &Producer, list);

    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);  

    DLDestroy(list);  

    return EXIT_SUCCESS; 
}

void *Producer(void *arg)
{
    int *products = DLGetData(DLBegin(arg));
    int count = 0; 

    while (1)
    {
        pthread_mutex_lock(&lock); 
        if (*products < 10)
        {
            printf("%d\n", *products); 
            ++*products;
        }
        ++count;
        pthread_mutex_unlock(&lock);

        if (count > 5500)
        {
            pthread_exit(NULL);
        }
    }


    (void)arg; 
    return NULL; 
}

void *Consumer(void *arg)
{
    int *products = DLGetData(DLBegin(arg));
    int count = 0; 
    
    while (1)
    {
        pthread_mutex_lock(&lock); 
        if (*products > 0)
        {
            printf("%d\n", *products); 
            --*products;
        }
        ++count;     
        pthread_mutex_unlock(&lock);   

        if (count > 5500)
        {
            pthread_exit(NULL);
        }
    }

    (void)arg;
    return NULL; 
}