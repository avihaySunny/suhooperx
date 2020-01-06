/*******************************************************************************
* Programmer: Avihay
* dll.h
* File: dll header
* Date: 20/5/19
* Version : 2
*******************************************************************************/

#ifndef __DLL_H__
#define __DLL_H__

#include <stddef.h>

typedef struct dll_node *dlist_iter_t; 

 /* metadata struct, contains only begin and end */
typedef struct dll_dlist dlist_t; 

/* Creates a new doubly linked list
 * Returns:
 *      The new doubly linked list.
 *      On Failure - NULL.
 */
dlist_t *DLCreate(void);


/* Destroys the doubly linked list
   May receive NULL. */
void DLDestroy(dlist_t *dlist);


/* Checks if the list is empty.
 * Returns:
 *      1 - list is empty
 *      0 - list is not empty  
 */
int DLIsEmpty(const dlist_t *dlist);

/* Returns:
 *	    1 - Iter is bad.
 *      0 - Iter is not bad.
 */
int DLIsBadIterator(const dlist_t *dlist, const dlist_iter_t iter);

/* Inserts the given data before the given iterator.
 * (undefined behaviour if the iterator points to start, dangling or NULL).
 * Returns:
 *		Iterator of the new element.
 *      On Failure - NULL.s
 */
dlist_iter_t DLInsertBefore(dlist_iter_t where, const void *data);


/* Deletes the GIVEN NODE.
 * (undefined if the element is end-of-list or start-of-list or NULL)
 * Returns:
 *      Iterator to the next node (after the erased). 
 */
dlist_iter_t DLErase(dlist_iter_t to_erase);


/* Pushes an element to the start of the list.
 * (undefined if passing a NULL pointer to list or DEADBEEF to data).
 * Returns:
 *      Iterator of the new pushed element.  
 */
dlist_iter_t DLPushFront(dlist_t *dlist, const void *data);


/* Pushes an element to the end of the list.
 * (undefined if passing a NULL pointer to list or DEADBEEF to data).
 * Returns:
 *      Iterator of the new pushed element.
 */
dlist_iter_t DLPushBack(dlist_t *dlist, const void *data);


/* Pops an element from the front of the list.
 * Undefined if popping from empty list. 
 */
void DLPopFront(dlist_t *dlist);


/* Pops an element from the end of the list.
 * Undefined if popping from empty list.
 */
void DLPopBack(dlist_t *dlist);


/* Splices the list at DEST, and inserts all elements between FROM (inclusive)
 * and TO (exclusive).
 * It is the caller's responsibility to assure that the resulted chain is valid. 
 * (undefined if 'FROM' is not before 'TO')
 * (undefined if DEST is between 'FROM' and 'TO')
 * Returns:
 *      Iterator to dest.
 */
dlist_iter_t DLSpliceBefore(dlist_iter_t dest, dlist_iter_t src_from, dlist_iter_t src_to);


/* Returns:
 *		Iterator to the first element of the list,
 *      (undefined if list is empty)   
 */
dlist_iter_t DLBegin(const dlist_t *dlist);


/* Returns:
 *		An (invalid for use) iterator to the position past the last element, 
 *      (end of list node).
 *      (undefined if list is empty)  
 */
dlist_iter_t DLEnd(const dlist_t *dlist);


/* Returns:
 *		Iterator to the next element.
 *      (undefined if trying to access end-of-list or when list is empty)  
 */
dlist_iter_t DLNext(const dlist_iter_t iter);


/* Returns:
 *		Iterator to the previous element. 
 *      (undefined if trying to access before the 1st elem. or when list is empty)
 */
dlist_iter_t DLPrev(const dlist_iter_t iter);


/* Compares the two given iterators.
 * Returns:
 *	    0 - iterators don't point to the same address.
 *      NON-ZERO - iterators point to the same address.
 */
int DLIsSameIterator(const dlist_iter_t iter1, const dlist_iter_t iter2);


/* Returns:
 *      The data of the given iterator. Iterator must be valid.      
 *      (undefined for using on the last element or when list is empty)  
 */
void *DLGetData(const dlist_iter_t iter);

               
/* Performs an action function on a list.
 * Returns:
 *      0 - action_func was successful for all elements.
 *      NON-ZERO - action_func was NOT successful for at least one element.
 *      In this case it exits, and assigns the affected element to failed_iter.
 *      User can provide NULL as failed iter.	
 */                  
int DLForEach(dlist_t *dlist,
              int(*action_func)(void *data, void *param),
              void *param, dlist_iter_t *failed_iter);


/* Iterates through all elements, 
 * until finding the element which matches the param., using the is_match func.
 * Returns:
 *      Iterator of the matching element.
 *	    If the element wasn’t found, returns NULL.
 */
dlist_iter_t DLFind(dlist_t *dlist,
                  int(*is_match)(const void *data, const void *param),
                  const void *param);
                                    
/* Returns:
 *		The number of elements in the given list
 */
size_t DLCount(const dlist_t *dlist);

#endif          /* dll  */


void DLPrint(const dlist_t *list);

int DLPrinter(void *data, void *param); 



