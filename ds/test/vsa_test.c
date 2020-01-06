/*******************************************************************************
* Programmer: Avihay Asraf
* vsa_test.c
* File: vsa testing
* Date: ה' מאי 30 10:40:43 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include "vsa.h"

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define SUCCESS (0)
#define FAIL (1)
#define WORD        (sizeof(size_t))
/*---------------------------------------------------------------------------*/
static int TestAllocation(void); 
static int TestFreeAndMerge(void);
static int TestMallocFail(void); 
static int TestFreeAll(void);

/*---------------------------------------------------------------------------*/
int main(void)
{
    size_t num_of_tests = 4; 
    size_t test_fail    = 0; 
    
    if (FAIL == TestAllocation())
    {
        puts(RED"Full Allocation failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestFreeAndMerge())
    {
        puts(RED"Free/Merge failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestMallocFail())
    {
        puts(RED"Malloc free and merge failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestFreeAll())
    {
        puts(RED"FreeAll failed"RESET);
        ++test_fail;
    }
  
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    return (EXIT_SUCCESS);
}
/*--------------------------------------------------------------------------*/
static int TestAllocation(void)
{
    size_t buf_size = 1500; 
    size_t fails = 0; 
    void *space = malloc(buf_size); 
    void *new_space = NULL; 
    vsa_t *vsa = NULL; 
    memset(space, 0, buf_size);
        /*test over allocation*/
    vsa = VSAInit(space, buf_size); 
    new_space = VSAAlloc(vsa, buf_size);
    
    (NULL == new_space) ? (0) : (++fails);

        /*checks one alloc one free*/ 
    new_space = VSAAlloc(vsa, 50); 
    (new_space != NULL) ? (0) : (++fails);

    VSAFree(new_space);
        /*check alignement*/
    new_space = VSAAlloc(vsa, 97); 
    ((size_t)new_space % 8 == 0) ? (0) : (++fails); 
    VSAFree(new_space);  
        /*checks address is a part of buffer*/
    new_space = VSAAlloc(vsa, 90); 
    ((size_t)(new_space) > (size_t)(space)) ? (0) : (++fails);   
    
    free(space); 
    
    return ((fails == 0 )? (SUCCESS) : (FAIL));    
}

/*--------------------------------------------------------------------------*/
static int TestFreeAndMerge(void)
{
    size_t buf_size = 5000; 
    int i = 0; 
    int fails = 0; 
    char space[5000] = {0}; 
    void *vec[100] = {NULL}; 
    vsa_t *vsa = VSAInit(&space, buf_size);
    
    for (i = 0; i < 100; ++i)
    {
        vec[i] = VSAAlloc(vsa, 50);
    }
    
    ((NULL == VSAAlloc(vsa, 200)) ? (0) : (++fails));
    
    for (i = 5; i < 10; ++i)
    {
        VSAFree(vec[i]);
    }
    
    ((NULL != VSAAlloc(vsa, 200)) ? (0) : (++fails));
     
    for (i = 20; i < 30; ++i)
    {
        VSAFree(vec[i]);
    }
    
    ((NULL != VSAAlloc(vsa, 550)) ? (0) : (++fails));    
    ((NULL != VSAAlloc(vsa, 50)) ? (0) : (++fails));
    ((NULL != VSAAlloc(vsa, 150)) ? (0) : (++fails));    
       
    return ((0 == fails) ? (SUCCESS) : (FAIL));
}
/*---------------------------------------------------------------------------*/
static int TestMallocFail(void)
{
    size_t buf_size = 1500; 
    int i = 0; 
    size_t fails = 0; 
    char space[1500] = {0}; 
    void *add_vec[50] = {NULL}; 
    vsa_t *vsa = NULL; 
    memset(space, 0, buf_size);
    
    vsa = VSAInit(&space, buf_size);
    
    for (i = 0; i < 25; ++i)
    {
        add_vec[i] = VSAAlloc(vsa, 100);
    } 
    
    for (i = 3; i < 10; ++i)
    {
        VSAFree(add_vec[i]);
    }
   
    add_vec[30] = VSAAlloc(vsa, 1500);
    (add_vec[30] == NULL) ? (0) : (++fails); 
    add_vec[30] = VSAAlloc(vsa, 350);
    (add_vec[30] == NULL) ? (++fails) : (0); 
    
    return ((fails == 0) ? (SUCCESS) : (FAIL));
}

static int TestFreeAll(void)
{
    size_t buf_size = 5000; 
    int i           = 0; 
    char mem[5000] = {0};
    size_t fails    = 0; 
    void *arr[1000]   = {NULL};
     
    vsa_t *vsa = VSAInit(&mem, buf_size);
    
    for (i =0; i < 1000; ++i)
    {
        arr[i] = VSAAlloc(vsa, 5);
        
    }
    
    (NULL == VSAAlloc(vsa, 100) ? (0): (++fails));
    
    for (i =0; i < 1000; ++i)
    {
        VSAFree(arr[i]);
    }
    
    (NULL == VSAAlloc(vsa, 4950) ? (++fails): (0));
    
    return ((fails == 0) ? (SUCCESS) : (FAIL)); 
}
   
/*---------------------------------------------------------------------------*/




