#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE (100)

pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sema_read = {0};
sem_t sema_write = {0};

typedef struct cbuf
{
	int buf[SIZE];
	int writer;
	int reader;
} cbuf_t;

static void Push(cbuf_t *cbuf, int data);
static int Pop(cbuf_t *cbuf);
static void *Producer(void *buffer);
static void *Consumer(void *buffer);

int main(void)
{
	size_t i = 0;
	cbuf_t buffer = {0};
	pthread_t consumer_threads[3] = {0};
	pthread_t producer_threads[3] = {0};
	
	sem_init(&sema_read, 0, 0);
	sem_init(&sema_write, 0, SIZE);
	for (i = 0; i < 3; i +=2)
	{
		pthread_create(&producer_threads[i], NULL, Producer, &buffer);
		pthread_create(&consumer_threads[i + 1], NULL, Consumer, &buffer);
	}
	for (i = 0; i < 3; ++i)
	{
		pthread_join(producer_threads[i], NULL);
		pthread_join(consumer_threads[i], NULL);
	}

	sem_destroy(&sema_read);
	sem_destroy(&sema_write);

	return EXIT_SUCCESS;
}

static void *Producer(void *buffer)
{
	int data = 0;

	while (1)
	{
		sem_wait(&sema_write);
		pthread_mutex_lock(&write_lock);
		Push(buffer, ++data);
		printf("writer: %d\n", data);
		pthread_mutex_unlock(&write_lock);
		sem_post(&sema_read);

		 if (5000 == data)
		{
			pthread_exit(NULL);
		} 
	}

	return NULL;
}

static void *Consumer(void *buffer)
{
	while (1)
	{
		int data = 0;
		sem_wait(&sema_read);
		pthread_mutex_lock(&read_lock);
		data = Pop(buffer);
		printf("reader: %d\n", data);
		sem_post(&sema_write);
		pthread_mutex_unlock(&read_lock);

	 	if (5000 == data)
		{
			pthread_exit(NULL);
		} 
	}
	
	return NULL;
}

static void Push(cbuf_t *cbuf, int data)
{
	assert(cbuf);

	++cbuf->writer;
	cbuf->buf[cbuf->writer % SIZE] = data;
}

static int Pop(cbuf_t *cbuf)
{
	assert(cbuf);

	++cbuf->reader;
	return cbuf->buf[cbuf->reader % SIZE];
}


