#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>
#include <semaphore.h>
#include <errno.h>

#include "../ds/include/cbuf.h"

#define SIZE 10
#define RESET_WRITER(x) ((x > SIZE) ? (x = 0) : (x))


pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
sem_t reader_sem = {0}; 
sem_t writer_sem = {0};

void *Consumer(void *arg);
void *Producer(void *arg); 

int main (void)
{   
    size_t i = 0; 
    pthread_t consumer[2], producer[2];
    cbuf_t *buffer = CBufCreate(sizeof(int) * SIZE); 
    
    sem_init(&reader_sem, 0, 1);
    sem_init(&writer_sem, 0, SIZE);

    for (i = 0; i < 2; ++i)
    {   
        pthread_create(&producer[i], NULL, &Producer, buffer);
        pthread_create(&consumer[i], NULL, &Consumer, buffer);
    }
   
    for (i = 0 ; i < 2; ++i)
    {
        pthread_join(producer[i], NULL);
        pthread_join(consumer[i], NULL);
    }
      
    CBufDestroy(buffer);
    
    for (i = 0 ; i < 2; ++i)
    {
    sem_destroy(&reader_sem);
    sem_destroy(&writer_sem);
    }

    return EXIT_SUCCESS; 
}

void *Producer(void *arg)
{
    int to_write = 0;  
     
    while (1)
    {
        sem_wait(&writer_sem);
        to_write = rand() % 50; 

        if (CBufGetFreeSpace(arg) > sizeof(int))
        {  
            pthread_mutex_lock(&lock); 
            CBufWrite(arg, &to_write, sizeof(int));
            printf("free : %ld\n", CBufGetFreeSpace(arg));
            printf("pros : %d\n", to_write);
            sem_post(&reader_sem);   
            pthread_mutex_unlock(&lock); 
            
        }    

        
        /* RESET_WRITER(to_write); */
    }

    return NULL; 
}

void *Consumer(void *arg)
{
    int to_read = 0; 
     
    while (1)
    {
        sem_wait(&reader_sem);
        pthread_mutex_lock(&lock); 
        CBufRead(arg, &to_read, sizeof(to_read)); 
        sem_post(&writer_sem); 
        printf("cons : %d\n", to_read);
        pthread_mutex_unlock(&lock);      
              
    }

    (void)arg; 
    return NULL; 
}