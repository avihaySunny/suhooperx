/*******************************************************************************
* Programmer: Avihay
* bst.h
* File: bst header
* Date: ג' יונ 11 12:56:52 IDT 2019
*******************************************************************************/

#ifndef __BST_H__
#define __BST_H__

#include <stddef.h>    /* size_t  */

typedef struct binary_search_tree bst_t; 

typedef struct bst_node *iter_t; 

/* Creates BST structre, returns null on failure , compare function MUST BE VALID*/
bst_t *BSTCreate(int (*compare)(const void *dataA, const void *dataB)); 

/*Destroys a tree, may recieve null */ 
void BSTDestroy(bst_t *tree); 

/* inserts data in new node, returns iterator upon success, null otherwise*/
iter_t BSTInsert(bst_t *tree, void *data); 

/* Removes given iter, returns iter node's data*/
void *BSTRemove(iter_t iter); 

int BSTForEach(iter_t from, iter_t to, int (*action)(const void *data, void *param), void *param);
															
iter_t BSTFind(const bst_t *tree, const void *search_param);

/* Returns the the most left value, invalid for empty tree*/
iter_t BSTBegin(const bst_t *tree); 

/* Returns the the most right value, invalid for empty tree*/
iter_t BSTEnd(const bst_t *tree); 

/* Returns iter to next ordered tree node, may return null*/
iter_t BSTNext(iter_t iter); 

/* Returns iter to prev ordered tree node, may return null*/
iter_t BSTPrev(iter_t iter); 
/* Returns number of childern including root*/
size_t BSTSize(const bst_t *tree); 

int BSTIsEmpty(const bst_t *tree); 

const void *BSTGetData(const iter_t iter);


#endif          /* __BST_H__  */








