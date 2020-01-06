#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>

volatile int to_produce = 0; 
volatile int to_consume  = 1;

int glob = 0; 

void *Consumer(void *arg);
void *Producer(void *arg); 

int main (void)
{   
    pthread_t consumer, producer; 
    
    pthread_create(&producer, NULL, &Consumer, NULL);
    pthread_create(&consumer, NULL, &Producer, NULL);
    
    pthread_join(consumer, NULL);
    pthread_join(producer, NULL);  

    return EXIT_SUCCESS; 
}

void *Producer(void *arg)
{
    while (1)
    {
        while (__sync_lock_test_and_set(&to_produce, 1))
        {
            continue; 
        }
        
        ++glob;
        printf("%d\n", glob); 
        __sync_lock_release(&to_consume);

    }

    return NULL; 
}

void *Consumer(void *arg)
{
    while (1)
    {
        while(__sync_lock_test_and_set(&to_consume, 1))
        {
            continue; 
        } 

        --glob; 
        printf("%d\n", glob);
        __sync_lock_release(&to_produce);    
    }

    return NULL; 
}