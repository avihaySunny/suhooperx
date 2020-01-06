/*******************************************************************************
* Programmer: Avihay
* sorted.h
* File: sorted header
* Date: ב' מאי 20 16:51:38 IDT 2019
*******************************************************************************/

#ifndef __SORTED_H__
#define __SORTED_H__

typedef void  *slist_iter_t; 
typedef struct sorted_list slist_t;

/* Creates a new sorted list. Left - existing data, right - new data.
 * Is_before checks is left before right. 
 * Is before must be a valid function, sending NULL would result in unexpected
 * behaviour. 
 * Returns:
 *      The new sorted list.    
 *      On Failure - NULL.
 *      Is_before function return status:
 *      1 - left SHOULD BE inserted before right. 
 *      0 - Otherwise. 
 */
slist_t *SortedListCreate(int(*is_before)(const void *left, const void *right));


/* Destroys the sorted list
 * May receive NULL. 
 */ 
void SortedListDestroy(slist_t *slist);


size_t SortedListCount(const slist_t *slist);


/* Checks if the list is empty.
 * Returns:
 *      1 - list is empty
 *      0 - list is not empty  
 */
int SortedListIsEmpty(const slist_t *slist);


/* Deletes the GIVEN NODE.
 * (undefined if the element is end-of-list or start-of-list or NULL)
 * Returns:
 *      Iterator to the next node (after the erased).
 */
slist_iter_t SortedListErase(slist_iter_t iter);


/* Inserts the given data to the sorted place.
 * (undefined behaviour if the iterator points to start, dangling or NULL).
 * Returns:
 *		Iterator of the new element.
 *      On Failure - NULL. 
 */
slist_iter_t SortedListInsert(slist_t *slist, const void *data);


/* Pops an element from the front of the list.
 * Undefined if popping from empty list. 
 * Returns:
 *      Data of the popped element.
 */
void *SortedListPopFront(slist_t *slist);  


/* Pops an element from the end of the list.
 * Undefined if popping from empty list.
 * Returns:
 *      Data of the popped element.
 */
void *SortedListPopBack(slist_t *slist);   


/* Returns:
 *		Iterator to the first element of the list,
 *      (undefined if list is empty)   
 */
slist_iter_t SortedListBegin(const slist_t *slist);


/* Returns:
 *		An (invalid for use) iterator to the position past the last element, 
 *      (end of list node).
 */
slist_iter_t SortedListEnd(const slist_t *slist);


/* Returns:
 *		Iterator to the next element.
 *      (undefined if trying to access end-of-list or when list is empty)  
 */
slist_iter_t SortedListNext(const slist_iter_t iter);


/* Returns:
 *		Iterator to the previous element. 
 *      (undefined if trying to access before the 1st elem. or when list is empty)
 */
slist_iter_t SortedListPrev(const slist_iter_t iter);


/* Compares the two given iterators.
 * Returns:
 *	    0 - iterators don't point to the same address.
 *      NON-ZERO - iterators point to the same address.
 */
int SortedListIsSameIterator(const slist_iter_t iter1,
 							 const slist_iter_t iter2);

/* Returns:
 *	    1 - Iter is bad (if it is NULL, or End of list).
 *      0 - Iter is not bad.
 */
int SortedListIsBadIterator(const slist_t *slist, const slist_iter_t iter);  


/* Returns:
 *      The data of the given iterator. Iterator must be valid.      
 *      (undefined for using on the last element or when list is empty)  
 */
void *SortedListGetData(const slist_iter_t iter);


/* Performs an action function on a list.
 * Returns:
 *      0 - action_func was successful for all elements.
 *      NON-ZERO - action_func was NOT successful for at least one element.
 *      In this case it exits, and assigns the affected element to failed_iter.
 *      User can provide NULL as failed iter.	
 */                    
int SortedListForEach(slist_t *slist,
               	  int(*action_func)(void *data, void *param),
                  void *param, slist_iter_t *failed_iter);


/* Iterates through all elements, 
 * until finding the element which matches the param., using the is_match func.
 * Returns:
 *      Iterator of the matching element.
 *	    If the element wasn’t found, returns NULL.
 */
slist_iter_t  SortedListFind(slist_t *slist,
                    int(*is_match)(const void *data, const void *param),
                    const void *param);
                    
/* Merges the list into DEST in a sorted place. 
 * It is the caller's responsibility to assure that the resulted chain is valid. 
 * Returns:
 *      Iterator to dest.
 */      
slist_t *SortedListMerge(slist_t *dest, slist_t *src); 

void SortedListPrint(slist_t *slist);


#endif          /* sorted  */







