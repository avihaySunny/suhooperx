/*******************************************************************************
* Programmer: Avihay Asraf
* pq_heap_test.c
* File: pq_heap testing
* Date: ד' יונ 26 14:23:26 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */

#include "pq_heap.h"

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
static int IsSorted(size_t *arr, size_t size);
/*--------------------Test-Functions-Declaration--------------------------*/
static int TestCreateDestroy(void);
static int TestSimpleInsert(void);
static int TestPQRemove(void) ;
static int TestSimpleRemove(void);
static int TestEnqueue(void);

/*-----------------------------MAIN---------------------------------------*/
int main(void)
{
    TestCreateDestroy();
    TestSimpleInsert();
    TestEnqueue();
    TestSimpleRemove();
    if (FAIL == TestPQRemove())
    {
        puts ("REMOVE FAILED");
    }

    return (EXIT_SUCCESS);
}
/*-----------------------------Test-Functions-----------------------------*/
static int TestCreateDestroy(void)
{
    pq_t *pq = PQCreate(CmpData);
    if (NULL == pq)
    {
        puts ("fail create line 103");
        return FAIL; 
    }
    
    if(!PQIsEmpty(pq))
    {
        puts ("PQ ISNT EMPTY line 109");
        return FAIL;
    }

    PQDestroy(pq);
    return SUCCESS;
}
/* ----------------------------------------------------------- */
static int TestSimpleInsert(void)
{
    size_t fails = 0; 
    size_t item_one = 0; 
    pq_t *pq = PQCreate(CmpData);
    if (NULL == pq)
    {
        return FAIL; 
    }

    PQEnqueue(pq, &item_one); 
    if (1 == PQIsEmpty(pq))
    {
        puts("error insert line 132");
        ++fails;
    }
    if(1 != PQSize(pq))
    {
        puts("error insert size line 137");
        ++fails;
    }

    PQDestroy(pq);
    return (!fails) ? (SUCCESS) : (FAIL); 
}

static int TestEnqueue(void)
{
    size_t fails = 0; 
    size_t items[] = {1, 12, 4, 5, 2, 3, 8, 11, 21, 54, 32 , 24, 56, 19, 23, 9, 12};
    size_t size = sizeof(items)/sizeof(items[0]);
    size_t *pq_array = (size_t*)malloc(size * sizeof(size_t));
    size_t i = 0; 
    pq_t *pq = PQCreate(CmpData);
    if (NULL == pq)
    {
        return FAIL; 
    }

    for (i = 0; i < size; ++i)
    {
        if (-1 == PQEnqueue(pq, &items[i]))
        {
            puts("error enqueue line 138");
            ++fails;
        }
    }
    if (size != PQSize(pq))
    {
        ++fails;
    }

    for (i = 0; i < size; ++i)
    {
        pq_array[i] = *(size_t*)PQDequeue(pq);
    }

    if(!IsSorted(pq_array, size))
    {
        puts ("not sorted line 134");
        ++fails;
    }

    free(pq_array);
    PQDestroy(pq);

    return (!fails) ? (SUCCESS) : (FAIL);  
}

static int TestSimpleRemove(void)
{
    int fails = 0; 
    size_t item = 15; 
    size_t cpy_itm = 15; 
    size_t is_found = 0;
    pq_t *pq = PQCreate(CmpData);
    if (NULL == pq)
    {
        return FAIL;
    }

    PQEnqueue(pq, &item);
    is_found = *(size_t*)PQRemove(pq, Find, &cpy_itm);
    if (is_found != cpy_itm)
    {
        puts ("simple remove error line 153");
        ++fails;
    }
    if(!PQIsEmpty(pq))
    {
        puts("pq not empty error line 159");
        ++fails;
    }

    PQDestroy(pq);
    return SUCCESS;
}

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
    
    return (successes == 2) ? (SUCCESS) : (FAIL) ; 
    
}
/*-------------------HelperFunction-Declarations-------------------------*/
static int CmpData(const void *dataA, const void *dataB)
{
    assert(dataA);
    assert(dataB); 
    
    return (*(int*)dataA > *(int*)dataB);   
}
/*---------------------------------------------------------------------------*/
static int Find(const void *dataA, const void *dataB)
{
    return (*(int*)dataA == *(int*)dataB);
}

static int IsSorted(size_t *arr, size_t size)
{
    size_t i = 0;

    assert(arr);

    for (i = 0; i < size - 1; i++)
    {
        if (arr[i] < arr[i + 1])
        {
            return 0;
        }
    }

    return 1; 
}