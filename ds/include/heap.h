/*******************************************************************************
* Programmer: Avihay
* heap.h
* File: heap header
* Date: ב' יונ 24 15:26:50 IDT 2019
*******************************************************************************/

#ifndef __FS6768_HEAP
#define __FS6768_HEAP

#include <stddef.h>		/*	size_t	*/

/*============================ typedefs ======================================*/

typedef int (*is_before_t)(const void *before, const void *after);
typedef int (*is_match_t)(const void *data, const void *to_compare);

typedef struct heap heap_t;
/*=========================== Function Prototypes ============================*/

/* Creates the admin struct for Heap DS. Returns pointer to the DS
   Returns NULL if creation has failed                                        */
heap_t *HEAPCreate(is_before_t is_before);

/* Destroys the given heap DS                                                 */
void HEAPDestroy(heap_t *heap);

/* Inserts data into the heap. Return success(0)/failure(1) status            */
int HEAPInsert(heap_t *heap, void *data);

/* Removes given data from the heap. Doesn't do anything if data is not
   present in the heap                                                        */
void HEAPRemove(heap_t *heap, void *data, is_match_t match_func);

/* Returns the number of elements currently in the heap                       */
size_t HEAPSize(const heap_t *heap);

/* Returns boolean true if heap is empty, false otherwise                     */
int HEAPIsEmpty(const heap_t *heap);

/* Removes the first element in the heap                                      */
void HEAPPop(heap_t *heap);

/* Returns a void pointer to the first element in the heap                    */
void *HEAPPeek(const heap_t *heap);

#endif /* HEAP */



