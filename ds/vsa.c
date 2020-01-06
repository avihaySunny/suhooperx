/*******************************************************************************
* Programmer: Avihay Asraf
* vsa.c
* File: vsa code
* Date:
*******************************************************************************/

/******************************************************************************/
#include <assert.h> 	    /* assert                                   */
#include <stdio.h>          /*puts                                      */
#include <sys/types.h>      /*ssize_t                                   */
#include <string.h>         /*memset                                     */
#include <limits.h>
#include "vsa.h"

#define WORD        (sizeof(size_t))
#define DEADBEEF ((void *)0xDEADBEEF)
#define ABS(a) ((a < 0) ? (-a) : (a))
#define META_SIZE sizeof(block_t)
#ifndef  NDEBUG
#define DBG(x)  x
#else
#define DBG(x)
#endif

typedef struct block_data block_t;

struct block_data
{
    DBG(void *deadbeef;)
    ssize_t free_mem;
};

struct variable_allocator
{
    size_t overall_size;
};

/*--------------------------------------------------------------------------*/
static size_t AdjustedBlockSize(size_t block_size, size_t overall_size);
static block_t *VSAEnd(vsa_t *vsa);
static block_t *NextBlock(block_t *ptr);
static void VSAMerge(block_t *block, block_t *end, size_t block_size);
static block_t *VSASplitBlock(block_t *to_split, size_t block_size);
static block_t *FindBlock(block_t *block, size_t block_size, block_t *end);

/*--------------------------------------------------------------------------*/
vsa_t *VSAInit(void *buff, size_t buf_size)
{
    vsa_t *vsa = buff;
    block_t *block = (block_t*)(vsa + 1);

    assert (buff);

    if (0 == buf_size)
    {
        return NULL;
    }

    vsa->overall_size = buf_size - sizeof(vsa_t) - META_SIZE;
    block->free_mem = vsa->overall_size;
    DBG(block->deadbeef = DEADBEEF;)

    return (vsa);
}
void *VSAAlloc(vsa_t *vsa, size_t block_size)
{
    block_t *block = (block_t*)(vsa + 1);

    assert(vsa);

    if ((block_size == 0) || (block_size > vsa->overall_size))
    {
        return NULL;
    }

    block_size = AdjustedBlockSize(block_size, vsa->overall_size);
    block = FindBlock(block, block_size, VSAEnd(vsa));
    if (NULL == block)
    {
        return NULL;
    }

    return (VSASplitBlock(block, block_size) + 1);

}

void VSAFree(void *block_ptr)
{
    block_t *block = block_ptr;

    if (NULL == block)
    {
        return ;
    }

    --block;
    block->free_mem = ABS(block->free_mem);
}

static block_t *VSAEnd(vsa_t *vsa)
{
    assert(vsa);

    return ((block_t*)((char*)vsa + vsa->overall_size));
}

static size_t AdjustedBlockSize(size_t block_size, size_t overall_size)
{
    size_t reminder = 0;
    
    block_size += (WORD - block_size % WORD) & (WORD - 1);
    reminder = overall_size - block_size;
    if (reminder <= META_SIZE)
    {
        block_size += reminder;
    }

    return block_size;
}

static block_t *VSASplitBlock(block_t *to_split, size_t block_size)
{
    block_t *new_stub = to_split;
    size_t available = 0;

    assert (to_split);
    available = to_split->free_mem;
    to_split->free_mem = -block_size;

    if (available > block_size)
    { 
        new_stub = NextBlock(to_split);
        new_stub->free_mem = available - block_size - META_SIZE;
        DBG(new_stub->deadbeef = DEADBEEF;)
    }

    return (to_split);
}

static void VSAMerge(block_t *block, block_t *end, size_t block_size)
{
    block_t *runner = block;
    ssize_t sum = -WORD;

    assert(block);

    while ( runner < end        &&
           runner->free_mem > 0 &&
           sum < (ssize_t)block_size )
    {
        sum += (ssize_t)runner->free_mem + META_SIZE;
        if (sum >= (ssize_t)block_size)
        {   
            block->free_mem = sum - META_SIZE;

            break;
        }

        runner = NextBlock(runner);
    }
}

static block_t *FindBlock(block_t *block, size_t block_size, block_t *end)
{
    block_t *runner = block;

    assert(block);

    while (runner < end)
    {
        if (runner->free_mem > 0 && runner->free_mem < (ssize_t)block_size)
        {
            VSAMerge(runner, end, block_size);
        }
        if (runner->free_mem >= (ssize_t)block_size)
        {
            return runner;
        }

        runner = NextBlock(runner);
    }
    
    return NULL; 
}

static block_t *NextBlock(block_t *block)
{
    assert(block);

    return (block_t*)((size_t)block + META_SIZE + ABS(block->free_mem));
}



