/*******************************************************************************
* Programmer: Avihay
* pq.h
* File: pq header
* Date:     
*******************************************************************************/

#ifndef __PQ_H__
#define __PQ_H__

#include <stddef.h>

typedef struct priority_queue pq_t;

/* Creates a new priority queue. Returns the adress of the queue.
 */
pq_t *PQCreate(int(*is_before)(const void* data, const void *param));

/* Destroys the queue and frees the memory used by the queue.
 */
void PQDestroy(pq_t *pq);

/* Inserts data into the queue. Returns 0 on success and -1 on failure. 
 */
int PQEnqueue(pq_t *pq, const void *data); 

/* Removes the most urgent item from the queue and returns its data. 
 */
void *PQDequeue(pq_t *pq);

/* Returns the data of the most urgent item 
 */
void *PQPeek(const pq_t *pq);

/* Returns a bool -- nonzero if the queue is empty and zero if the queue is empty.
 */
int PQIsEmpty(const pq_t *pq);

/* Returns the size of the queue. 
 */
size_t PQSize(const pq_t *pq);

/* Removes the first element for which is_found returns non-null (if such element exists) and returns its data.
 */
void *PQRemove(pq_t *pq, int(*is_found)(const void* data, const void *param),                                           const void *param);

void PQPrint(pq_t *pq);
#endif /* #define __PQ_H__ */

