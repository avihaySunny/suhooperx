#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <assert.h>

#define CONSUMER_NUM (3) 
#define DATA_LIM (500)
pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_data_to_read; 
sem_t okay_to_produce = {0};

static void *Producer(void *arg);
static void *Consumer(void *arg);
static int data_to_read = 0;
static int spur_flag = 1; 
int main(void)
{
	size_t i = 0;
	pthread_t consumer_threads[CONSUMER_NUM] = {0};
	pthread_t producer_thread = {0};
	
    sem_init(&okay_to_produce,0, 0);
    pthread_cond_init(&cond_data_to_read, NULL);
    pthread_create(&producer_thread, NULL, Producer, NULL);
    
    for (i = 0; i < CONSUMER_NUM; ++i)
	{
		pthread_create(&consumer_threads[i], NULL, Consumer, NULL);
	}

    pthread_join(producer_thread, NULL);
	for (i = 0; i < CONSUMER_NUM; ++i)
	{
		pthread_join(consumer_threads[i], NULL);
	}

    sem_destroy(&okay_to_produce);
    pthread_cond_destroy(&cond_data_to_read);
    pthread_mutex_destroy(&read_lock);

	return EXIT_SUCCESS;
}

static void *Producer(void *arg)
{
    size_t i = 0; 

	while (1)
	{
        for (i = 0; i < CONSUMER_NUM; ++i)
        {
            sem_wait(&okay_to_produce);
        }    

        ++data_to_read; 

        pthread_mutex_lock(&read_lock);
        pthread_cond_broadcast(&cond_data_to_read);
        pthread_mutex_unlock(&read_lock);

        if (data_to_read == DATA_LIM)
        {
            pthread_exit(NULL);
        }
	}

    (void)arg;
	return NULL;
}

static void *Consumer(void *arg)
{  
	while (1)
	{
        printf("data : %d, thread_id  %ld \n", data_to_read, pthread_self()); 

        pthread_mutex_lock(&read_lock);
        sem_post(&okay_to_produce); 
        
        pthread_cond_wait(&cond_data_to_read, &read_lock);
        pthread_mutex_unlock(&read_lock);
        
        if (data_to_read == DATA_LIM)
        {
            pthread_exit(NULL);
        }
	}

	(void)arg;
	return NULL;
}



