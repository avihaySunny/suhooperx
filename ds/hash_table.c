/*******************************************************************************
* Programmer: Avihay Asraf
* hash_table.c
* File: hash_table code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */
#include "d_list.h"
#include "hash_table.h"

#define IDLE (0)
struct hash 
{
    dlist_t* *list_arr;
    size_t key_num;  
    size_t (*hash_func)(void *);
    int (*is_match)(const void*, const void*);
}; 

hash_t *HASHCreate(size_t (*hash_func)(void *data), size_t key_num, 
                        int (*is_match)(const void *dataA, const void *dataB))
{
    size_t i = 0; 
    hash_t *hash = (hash_t*)malloc(sizeof(hash_t)); 
    
    if (!hash)
    {
        return NULL; 
    }

    hash->list_arr = (dlist_t**)calloc(key_num, sizeof(void*));

    if (!hash->list_arr)
    {
        free(hash); 
        return NULL; 
    }
    
    for (i = 0; i < key_num; ++i)
    {
        hash->list_arr[i] = DLCreate();
        if (NULL == hash->list_arr[i])
        {
            hash->key_num = i; 
            HASHDestroy(hash);
            return NULL; 
        } 
    }

    hash->key_num = key_num; 
    hash->hash_func = hash_func;
    hash->is_match = is_match; 
    
    return hash;
} 

void HASHDestroy(hash_t *hash)
{
    size_t i = 0; 

    if (NULL == hash)
    {
        return; 
    }

    for (i = 0; i < hash->key_num; ++i)
    {
        DLDestroy(hash->list_arr[i]);
    }

    free(hash->list_arr);
    free(hash);
}

int HASHIsEmpty(const hash_t *hash)
{
    size_t i = 0;
    
    assert(hash);

    for (i = 0; i < hash->key_num; ++i)
    {
        if (!DLIsEmpty(hash->list_arr[i]))
        {
            return 0;
        }
    }

    return 1;
}

int HASHInsert(hash_t *hash, void *data)
{
    size_t indx = 0; 
    assert(hash);

    indx = hash->hash_func(data) % hash->key_num; 
    return (NULL == DLInsertBefore(DLEnd(hash->list_arr[indx]), data));
}

size_t HASHSize(const hash_t *hash)
{
    size_t count = 0, i = 0;

    assert (hash); 

    for (i = 0; i < hash->key_num; ++i)
    {
        count += DLCount(hash->list_arr[i]);
    }

    return count; 
}

void *HASHFind(const hash_t *hash, const void *data)
{
    size_t indx = 0; 
    void *found = NULL; 

    assert(hash); 
    
    indx = hash->hash_func((void*)data) % hash->key_num;
    found = DLFind(hash->list_arr[indx], hash->is_match, data);

    return (found == NULL ) ? (NULL) : (DLGetData(found));
}

void HASHRemove(hash_t *hash, void *data)
{
    size_t indx = 0; 
    void *found = NULL;
    
    assert(hash && data);

    indx = hash->hash_func(data) % hash->key_num; 
    found = DLFind(hash->list_arr[indx], hash->is_match, data);
    ((found == NULL) ? (IDLE) : (DLErase(found))); 
}

int HASHForEach(hash_t *hash, int (*action)(void*, void*), void *param)
{ 
    int status = 0; 
    size_t i = 0;

    assert(hash); 

    for (i = 0; i < hash->key_num; ++i)
    {
        status = DLForEach(hash->list_arr[i], action, param, NULL);
        if (0 != status)
        {
            return status; 
        }
    }

    return 0; 
}

