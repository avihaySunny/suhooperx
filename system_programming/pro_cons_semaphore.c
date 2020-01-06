#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>
#include <stdlib.h>

#define DATA_LIMIT (5000)
#define SIZE (100)
#define RESET_DATA(x) ((x > DATA_LIMIT) ? (x = 0) : (x))
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

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
sem_t sema_reader = {0};
sem_t sema_writer = {0};

int main(void)
{
	size_t i = 0;
	cbuf_t buffer = {0};
	pthread_t consumer_threaders[3] = {0};
	pthread_t producer_threaders[3] = {0};
	
	sem_init(&sema_reader, 0, 0);
	sem_init(&sema_writer, 0, SIZE);
	for (i = 0; i < 3; i +=2)
	{
		pthread_create(&producer_threaders[i], NULL, Producer, &buffer);
		pthread_create(&consumer_threaders[i + 1], NULL, Consumer, &buffer);
	}
	for (i = 0; i < 3; ++i)
	{
		pthread_join(producer_threaders[i], NULL);
		pthread_join(consumer_threaders[i], NULL);
	}

	sem_destroy(&sema_reader);
	sem_destroy(&sema_writer);

	return EXIT_SUCCESS; 
}


static void *Producer(void *buffer)
{
	int data = 0;

	while (1)
	{
		sem_wait(&sema_writer);
		pthread_mutex_lock(&lock);
		Push(buffer, ++data);
		printf("writer: %d\n", data);
		pthread_mutex_unlock(&lock);
		sem_post(&sema_reader);

		if (15000 == data)
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
		sem_wait(&sema_reader);
		pthread_mutex_lock(&lock);
		data = Pop(buffer);
		printf("reader: %d\n", data);
		sem_post(&sema_writer);
		pthread_mutex_unlock(&lock);
        
		if (15000 == data)
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

