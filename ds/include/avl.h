/*******************************************************************************
* Programmer: Avihay
* avl.h
* File: avl header
* Date: ב' יונ 17 10:37:01 IDT 2019
*******************************************************************************/
#ifndef __AVL_H__ 
#define __AVL_H__
#include <stddef.h>
#include <sys/types.h>

typedef struct avl avl_t; 

/* Creates AVL structre, returns null on failure */
avl_t *AVLCreate(int (*compare)(const void *data, const void *key)); 

/*Destroys a tree, may recieve null */ 
void AVLDestroy(avl_t *tree); 

/* inserts data in new node null otherwise, return 0 on success */
int AVLInsert(avl_t *tree, void *key); 

/* Remove the node (if it exists) with KEY */
void AVLRemove(avl_t *tree, const void *key); 

/* Performs ACTION on every node in TREE in-order */
int AVLForEach(const avl_t *tree, 
    int (*action)(const void *data, void *param), void *param);
															
/* returns data matched by KEY if it exists or NULL otherwise */
const void *AVLFind(const avl_t *tree, const void *key); 

/* Return the number of nodes in TREE */
size_t AVLSize(const avl_t *tree); 

/* Returns the height of TREE */
size_t AVLHeight(const avl_t *tree);

/* Returns 0 if TREE is empty and non-zero TREE is empty */
int AVLIsEmpty(const avl_t *tree); 

ssize_t AVLGetBF(avl_t *tree); /*FOR TESTING, RETURNS THE ROOT BALANCE FACTOR */

#endif /* #define __AVL_ */


