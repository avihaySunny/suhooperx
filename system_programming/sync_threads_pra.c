#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

static void InitArr(void);
void *SumArray(void *arg);
void *ChangeArray(void *arg); 

int arr[10000] = {0};
size_t size = sizeof(arr)/sizeof(arr[0]);
pthread_mutex_t *mylock = NULL; 

int main (void)
{
    pthread_t sum_thread;
    void *stat = NULL;  
    pthread_t changer_thread; 
    size_t sum = 0; 

    mylock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(mylock, NULL);
    InitArr(); 
    pthread_create(&sum_thread, NULL, &SumArray, &sum);
    pthread_join(sum_thread, &stat); 
    pthread_create(&changer_thread, NULL, &ChangeArray, &sum); 
    /* 
    pthread_detach(changer_thread); 
    pthread_detach(sum_thread);
 */
    pthread_mutex_destroy(mylock);
    printf("%ld\n", sum); 

    return EXIT_SUCCESS; 
}

void *SumArray(void *arg)
{ 
    size_t i = 0; 
    
    if (0 != pthread_mutex_lock(mylock))
    {
        puts ("mutex lock failed\n"); 
    }
    
    for (i = 0; i < size; ++i)
    {
        *(size_t*)arg += arr[i];  
    }

    if (0 != pthread_mutex_unlock(mylock))
        {
            puts ("mutx unlock failed\n"); 
        } 
    
  
    return arg; 
}

void *ChangeArray(void *arg)
{
    size_t i = 0; 
    for (i = 0 ; i < size; ++i)
    {
        arr[i] = 0; 
    }

    return arg; 
}

static void InitArr(void)
{
    size_t i = 0; 
    for (i = 0; i < size; ++i)
    {
        arr[i] = i;  
    }
}



