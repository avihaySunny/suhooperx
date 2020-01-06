/*******************************************************************************
* Programmer: Avihay Asraf
* pq_test.c
* File: pq testing
* Date: 22/5/19
*******************************************************************************/
/*--------------------TEST DESCRYPTION-----------------------------------------
*               1. Tests IsEmpty on empty and unempty list         
*               2. Tests insert (Enqueue) in right order
*               3. Tests Dequeue from list in right order and value according 
*                  priority criteria. 
*               4. Test removing element from queue using the right search   
*                  Tests Find (uses ForEach) and looks for data in list and for
*                  data not on the list, checks for correct returns;
*-----------------------------------------------------------------------------*/
#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */

#include "./include/p_queue.h"
/*---------------------------------------------------------------------------*/
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"
                    
#define SUCCESS 0 
#define FAIL 1 
#define STRSIZE (6)

/*-------------------HelperFunction-Declarations-------------------------*/
static int CmpData(const void *dataA, const void *dataB);
static int Find(const void *dataA, const void *dataB);

/*--------------------Test-Functions-Declaration--------------------------*/
static int TestPQIsEmpty(void);
static int TestPQEnqueue(void);
static int TestPQDequeue(void);
static int TestPQRemove(void) ;

/*-----------------------------MAIN---------------------------------------*/

int main(void)
{
    size_t num_of_tests = 4; 
    size_t test_fail    = 0; 
   
     if (FAIL == TestPQIsEmpty())
    {
        puts(RED"Priority queue IsEmpty Test Fail"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestPQRemove())
    {
        puts(RED"Priority queue Remove Test Fail"RESET);
        ++test_fail;
    }
    if (FAIL == TestPQEnqueue())
    {
        puts(RED"Priority queue Enqueue Test Fail"RESET);
        ++test_fail;
    }
    
     if (FAIL == TestPQDequeue())
    {
        puts(RED"Priority queue Dequeue Test Fail"RESET);
        ++test_fail;
    } */
   
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    return (EXIT_SUCCESS);
        
}
/*-----------------------------Test-Functions-----------------------------*/
static int TestPQIsEmpty(void)
{
    int successes = 0;
    pq_t *pq = PQCreate(CmpData);
    if (NULL == pq)
    {
        return FAIL; 
    } 
    
    (PQIsEmpty(pq)) ? (++successes) : (successes); 
    PQEnqueue(pq, &successes); 
    (!PQIsEmpty(pq)) ? (++successes) : (successes); 
    PQDestroy(pq); 
    
    return (!(successes == 2));
}
/*---------------------------------------------------------------------------*/
static int TestPQRemove(void)
{
    int i = 0; 
    int successes = 0; 
    int arr[15] = {0};
    int found = 14;     /*data that will exist in queue     */
    int not_found = 18; /*data that will not exist in queue */
    
    pq_t *pq = PQCreate(CmpData);
    
    for (i = 0; i < 15; ++i)
    {
        arr[i] = i; 
        PQEnqueue(pq, &arr[i]);
    }
    
    ((found == *(int*)PQRemove(pq,Find,&found))? (++successes) : (successes));
    ((NULL == PQRemove(pq, Find, &not_found))? (++successes) : (successes));
    PQDestroy(pq);
    
    return (!(successes == 2));
    
}

/*---------------------------------------------------------------------------*/
static int TestPQEnqueue(void)
{
    int i = 0; 
    size_t size = 0; 
    int successes = 0; 
    int arr[15] = {0};
    
    pq_t *pq = PQCreate(CmpData);
    
    for (i = 0; i < 15; ++i)
    {
        arr[i] = i; 
        successes += PQEnqueue(pq, &arr[i]);
    }
    
    size = PQSize(pq);
    PQDestroy(pq); 
    
    return(!((size == 15) && (successes == 0)));
}

/*---------------------------------------------------------------------------*/

static int TestPQDequeue(void)
{
    int i = 0; 
    int successes = 0; 
    int arr[15] = {0};
    
    pq_t *pq = PQCreate(CmpData);
    
    for (i = 0; i < 15; ++i)
    {
        arr[i] = i; 
        successes += PQEnqueue(pq, &arr[i]);
    }
    
    for (i = 0; i < 15; ++i)
    {   
        if (arr[i] != *(int*)PQDequeue(pq))
        {
            ++successes;
        }
    }
    
    i = PQIsEmpty(pq); 
    PQDestroy(pq); 
   
    return(!(i == 1  && (successes == 0)));
}

/*-------------------HelperFunction-Declarations-------------------------*/
static int CmpData(const void *dataA, const void *dataB)
{
    assert(dataA);
    assert(dataB); 
    
    return (*(int*)dataA < *(int*)dataB);   
}
/*---------------------------------------------------------------------------*/
static int Find(const void *dataA, const void *dataB)
{
    return (*(int*)dataA == *(int*)dataB);
}
