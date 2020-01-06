/*******************************************************************************
* Programmer: Avihay
* queue.h
* File: queue header
* Date: ה' מאי 16 09:59:10 IDT 2019
*******************************************************************************/

#ifndef __QUEUE_H__
#define __QUEUE_H__

typedef struct queue queue_t;

/* Creates new queue returns NULL On failure */
queue_t *QCreate(void);

void QDestroy(queue_t *q);

/* Add element to queue. Returns int(status 0 on success ) */
int QEnqueue(queue_t *q, void *data);

/* returns pointer to next data to be leave queue
*  queue must not be empty or behaviour is undefined*/
void *QPeek(const queue_t *q);

/* Remove element from top of the queue, returns it data. 
 if queue is empty behaviour is undefined*/
void *QDequeue(queue_t *q);

/* Counts number of queue_t element */
size_t QCount(const queue_t *q);

/* Returns 1 if empty queue, 0 otherwise*/
int QIsEmpty(const queue_t *q);

/* Appends src to dest, destroys src in process (queue, not data)
returns a pointer to dest queue must not be empty behaviour is undefined*/
queue_t *QAppend(queue_t *dest, queue_t *src);

#endif          /* queue  */







