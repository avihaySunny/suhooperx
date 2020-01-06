/*******************************************************************************
* Programmer: Avihay
* hash_table.h
* File: hash_table header
* Date: א' יונ 23 11:57:12 IDT 2019
*******************************************************************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

typedef struct hash hash_t;

/*  
*   creates a hash table with hash function given by user
*   and the number of keys options
*   may return NULL 
*/

hash_t *HASHCreate(size_t (*hash_func)(void *data), size_t key_num, int (*is_match)(const void *dataA, const void *dataB));

/*  
*   Destroy's has and all container inside 
*/
void HASHDestroy(hash_t *hash);

/*  
*   Inserts new data to hash table using user function..
*/
/*
 * inserts node according to has function, return 1 on failure, 0 success. 
 */
int HASHInsert(hash_t *hash, void *data);

/*removes a record from hash table using the hash function and search */
void HASHRemove(hash_t *hash, void *data);

/*  
*   Finds data in hash table, return ptr to data or 
*   null on empty search results, uses match provided
*   by user on creation
*/
void *HASHFind(const hash_t *hash, const void *data);

/*  
*   returns 1 for empty hash table  
*/

int HASHIsEmpty(const hash_t *hash); 

int HASHForEach(hash_t *hash, int (*action)(void*, void*), void *param);

size_t HASHSize(const hash_t *hash);


#endif          /* hash_table  */







