/*******************************************************************************
* Programmer: Amit Evron
* vector.h
* File: vector header
* Date: ג' מאי  7 15:29:54 IDT 2019
*******************************************************************************/
#include <stddef.h>         /* size_t */
#include <sys/types.h>      /*  ssize_t */

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"


#ifndef __VECTOR_H__
#define __VECTOR_H__

typedef struct dynamic_vector vect_t; 

#ifndef NDEBUG
    #define DBG(x) x
#else
    #define DBG(x)
#endif

/*      create the vector and struct element    */          
vect_t *VecCreate(size_t element_size, size_t max_elements); 

/*      free the array and leave no dangling pointer    */
void VecDestroy(vect_t *dv); 

/*      returns the address in index locatopn   */
void *VecGetItemAddress(const vect_t *dv, size_t index); 

/*      add data to dynamic vector  */ 
ssize_t VecPush(vect_t *dv, const void *data); 

/*      goes back an element    */
ssize_t VecPop(vect_t *dv);

/*      returns the number of ocupied memory  */
size_t VecGetSize(const vect_t *dv); 

/*      returns the size of allocated memory    */
size_t VecGetCapacity(const vect_t *dv); 

/*      reserve a n_element size of memory - big chunk  */
ssize_t VecReserve(vect_t *dv, size_t n_elements);

#ifndef NDEBUG 

/*  prints the vector - 2 options   */
void VecPrint(const vect_t *dv, void(print_element(void*)), size_t n_elements);

#endif 

#endif          /* vector  */



