/*******************************************************************************
* Programmer: Avihay
* vsa.h
* File: vsa header
* Date: ה' מאי 30 10:40:43 IDT 2019
*******************************************************************************/


#ifndef __VSA_H__
#define __VSA_H__

#include <stddef.h>

typedef struct variable_allocator vsa_t;

/* creates the module, return NULL if fails*/ 
vsa_t *VSAInit(void *buff, size_t buf_size);

/* Allocates memory from buffer if available, 
 * returns NULL if unsuccesfull/Insufficent memory*/
  
void *VSAAlloc(vsa_t *vsa, size_t block_size); 

/*Frees a memory given to user, pointer must be valid*/

void VSAFree(void *block_ptr);


#endif          /* vsa  */







