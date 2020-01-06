/*******************************************************************************
* Programmer: Avihay Asraf
* trie.c
* File: trie code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#include "trie.h"

#define AVAILABLE (0)
#define TAKEN (1)
#define LEFT (0)
#define RIGHT (1)

static int IsAvailable(trie_t *node);
static void SetNotAvailable(trie_t *node);
static void SetAvailable(trie_t *node);

struct trie_node
{
    int is_taken; 
    trie_t *child[2]; 
};

void TrieDestroy(trie_t *trie)
{
    if (trie == NULL)
    {
       return;  
    }

    TrieDestroy(trie->child[0]);
    TrieDestroy(trie->child[1]);

    free(trie);
}

trie_t *CreateTrieNode() 
{
    trie_t *node = (trie_t*)malloc(sizeof(trie_t)); 
    if (NULL == node)
    {
        return NULL; 
    }

    node->is_taken = 0; 
    node->child[0] = NULL; 
    node->child[1] = NULL;

    return node; 
}

static int IsAvailable(trie_t *node)
{
    return (node->is_taken == AVAILABLE); 
}

int InsertWithIP(trie_t *node,ip_t ip, size_t height)
{
    int status = 0; 
    
    assert(node);
    
    if (height == 0)
    {
        node->is_taken = 1; 
        return 1;  
    }
    
    if (!IsAvailable(node))
    {
        return 0; 
    }
     
    if (0 == status && NULL == node->child[LEFT])
    {
        node->child[LEFT] = CreateTrieNode(); 
    }
  
    if(0 == status && IsAvailable(node->child[LEFT])) 
    {
        UpdateIP(ip, 0); 
        status = InsertWithIP(node->child[LEFT], ip, height - 1); 
    } 

    if (0 == status && NULL == node->child[RIGHT])
    {
        node->child[RIGHT] = CreateTrieNode(); 
    }
    
    if(0 == status && IsAvailable(node->child[RIGHT]))
    {
        UpdateIP(ip, 1); 
        status = InsertWithIP(node->child[RIGHT], ip, height - 1);   
    }  

    SetNotAvailable(node); 
    return status; 
}

int InsertStaticIP(trie_t *node, ip_t static_ip, size_t height)
{
    int status = 0; 
    trie_t *next_node = NULL;

    if (height == 0)
    {
        if (node->is_taken == 1)
        {
            return 0; 
        }
        
        node->is_taken = 1; 
        return 1; 
    }

    next_node = node->child[GetNextBit(static_ip, height)]; 
    if (next_node == NULL)
    {
        next_node = node->child[GetNextBit(static_ip, height)] = CreateTrieNode();
    }

    status = InsertStaticIP(next_node, static_ip, height -1 );
    return status; 
}


int TrieFreeIP (trie_t *node, const ip_t ip_to_free, size_t height)
{
    int status = 0; 
    
    if (node == NULL)
    {
        return status; 
    }
    if (height == 0)
    {
        if (node->is_taken == 0)
        {
            return 0; 
        }
        
        node->is_taken = 0; 
        return 1; 
    }
    
    status = TrieFreeIP(node->child[GetNextBit(ip_to_free, height)], ip_to_free, height - 1);
    SetAvailable(node);
    
    return status; 
}

static void SetNotAvailable(trie_t *node)
{
    if (node->child[LEFT] != NULL && node->child[RIGHT] != NULL)
    {
        if (!IsAvailable(node->child[LEFT]) && !IsAvailable(node->child[RIGHT]))
        {
            node->is_taken = 1; 
        }
    }
}

static void SetAvailable(trie_t *node)
{
    if (node->child[LEFT] != NULL && node->child[RIGHT] != NULL)
    {
        if (IsAvailable(node->child[LEFT]) || IsAvailable(node->child[RIGHT]))
        {
            node->is_taken = 0; 
        }
    } 
}



