/*******************************************************************************
* Programmer: Avihay Asraf
* dll_test.c
* File: dll testing
* Date: 20/5/19
* Version : 2
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE                */

#include "./include/d_list.h"

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define UNUSED(a)   ((void)(a))  /* for unusued variables   */
#define SUCCESS  (0)
#define FAIL (1)

/*--------------------TEST DESCRYPTION-----------------------------------------
*               1. Tests create and destroy list         
*               2. Tests IsEmpty on empty and unempty list 
*               3. Tests all pop/push functions - adds data and checks to see 
*                  if it has been inserted to the right place. 
*               4. Tests Find (uses ForEach) and looks for data in list and for
*                  data not on the list, checks for correct returns;
*               5. Splices a list and appends it to another one, checks for 
*                  proper data. 
*               6. Tests count on empty list and on unempty.  
/---------------------------------------------------------------------------*/
static int DLFinder(void *data, void *param);/*for int testing*/ 
static int TestDLCreateDestroy(void); 
static int TestDLIsEmpty(void); 
static int TestDLPushFront(void); 
static int TestDLPushBack(void); 
static int TestDLPopFront(void); 
static int TestDLPopBack(void);
static int TestDLFind(void);
static int TestDLSplice(void);
static int TestDLCount(void);  
/*-----------------MAIN-------------------------------------------------------*/
 
int main(void)
{
    size_t num_of_tests = 9; 
    size_t test_fail = 0; 
    
    if (FAIL == TestDLCreateDestroy())
    {
        puts(RED"Test Create list fail"RESET);
        ++test_fail;
    }

    if (FAIL == TestDLIsEmpty())
    {    
        puts(RED"Test Is Empty fail"RESET);
        ++test_fail; 
    }
    
    if (FAIL == TestDLPushFront())
    {    
        puts(RED"Test Push Front fail"RESET);
        ++test_fail; 
    }
    
    if (FAIL == TestDLPushBack())
    {    
        puts(RED"Test Push Back fail"RESET);
        ++test_fail; 
    }
    
    if (FAIL == TestDLPopFront())
    {
        puts(RED"Test Pop Front fail"RESET);
        ++test_fail;   
    }
    
    if (FAIL == TestDLPopBack())
    {
        puts(RED"Test Pop Back fail"RESET);
        ++test_fail;   
    }
    
    if (FAIL == TestDLFind())
    {
        puts(RED"Test DLFind Fail");
        ++test_fail;
    }
    
    if (FAIL ==  TestDLSplice())
    {
        puts(RED"Test DL Splice Fail");
        ++test_fail;
    }
     
    if (FAIL ==  TestDLCount())
    {
        puts(RED"Test DL Splice Fail");
        ++test_fail;
    }
   

    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    return (EXIT_SUCCESS);
}

/*****************TEST--FUNCTIONS****************************/
static int TestDLCreateDestroy(void)
{
    dlist_t *list = DLCreate(); 
    if (NULL == list)
    {
        return (FAIL);
    }
    
    DLDestroy(list);
   
    return SUCCESS; 
}

static int TestDLIsEmpty(void)
{
    dlist_t *list = DLCreate(); 
    int successes = 0; 
    if (NULL == list)
    {
        return (FAIL);
    }  
    
    if (DLIsEmpty(list))
    {
        ++successes;  
    }
    
    DLPushBack(list, &successes);
    if(0 == DLIsEmpty(list))
    {
        ++successes;
    }
    
    DLDestroy(list); 
    
    return ((2 == successes) ? (SUCCESS) : (FAIL));
}

static int TestDLPushFront(void)
{
    int a = 5, i = 0; 
    dlist_t *list = DLCreate(); 
    
    if (NULL == list)
    {
        return (FAIL);
    } 
    
    for (i = 0; i < 5; ++i)
    {
        DLPushFront(list, &a); 
    }
    
    if ((a == *(int*)DLGetData(DLBegin(list))) && (5 == DLCount(list)))
    {
        DLDestroy(list); 
        list = NULL;
        
        return SUCCESS;
    }
    
    return FAIL; 
}

static int TestDLPushBack(void)
{
    int a = 5; 
    dlist_t *list = DLCreate(); 
    
    if (NULL == list)
    {
        return (FAIL);
    }
    
    DLPushBack(list, &a); 
    if (a != *(int*)DLGetData(DLBegin(list))) 
    {
        DLDestroy(list);
        list = NULL;
        
        return (FAIL);
    }
    
    DLPushBack(list, &a); 
    if (a != *(int*)DLGetData(DLNext(DLBegin(list)))) 
    {
        DLDestroy(list);
        list = NULL;
        
        return (FAIL);
    }
    
    DLDestroy(list);
    
    return (SUCCESS);
}

static int TestDLPopFront(void)
{
    int a = 5; 
    int b = 7; 
    dlist_t *list = DLCreate(); 
    
    if (NULL == list)
    {
        return (FAIL);
    }
    
    DLPushFront(list, &a);
    DLPushFront(list, &b);
    if (b != *(int*)DLGetData(DLBegin(list))) 
    {
        DLDestroy(list);
        list = NULL;
        
        return (FAIL);
    }
    
    DLPopFront(list); 
    if (a != *(int*)DLGetData(DLBegin(list))) 
    {
        DLDestroy(list);
        list = NULL;
        
        return (FAIL);
    }
    
    DLDestroy(list);
    list = NULL;
   
    return (SUCCESS);
}

static int TestDLPopBack(void)
{
    int a = 5; 
    int b = 7; 
    dlist_t *list = DLCreate(); 
    
    if (NULL == list)
    {
        return (FAIL);
    }
    
    DLPushBack(list, &a);
    DLPushBack(list, &b);
    if (b != *(int*)DLGetData(DLPrev(DLEnd(list)))) 
    {
        DLDestroy(list);
        list = NULL;
        
        return (FAIL);
    }
    
    DLPopBack(list); 
    if (a != *(int*)DLGetData(DLPrev(DLEnd(list)))) 
    {
        DLDestroy(list);
        list = NULL;
       
        return (FAIL);
    }
    
    DLDestroy(list);
    list = NULL;
   
    return (SUCCESS);
}

static int TestDLFind(void)
{
    static int arr[20] = {0};
    int found = 17;  
    int i = 0; 
    int successes = 0;
    dlist_t *list = DLCreate(); 
    dlist_iter_t found_ptr = NULL;
     
    if (NULL == list)
    {
        return (FAIL);
    }
    
    for (i = 0; i < 20; ++i)
    {
        arr[i] = i; 
        DLInsertBefore(DLEnd(list), &arr[i]);
    }
    
    found_ptr = DLFind(list,(int(*)(const void*,const void*)) DLFinder, &found);
    
    if(17 == *(int*)DLGetData(found_ptr))
    {
       ++successes;  
    }
    
    found = 26; 
    found_ptr = DLFind(list,(int(*)(const void*,const void*)) DLFinder, &found);
    if (NULL == found_ptr)
    {
        ++successes;
    }
    
    DLDestroy(list);
    
    return ((successes == 2) ? (SUCCESS) : (FAIL));
}

static int TestDLSplice(void)
{
    static int arr[10] = {0}; 
    static int arr2[10] = {0};
    int i = 0;
    int successes = 0;  
    dlist_iter_t src_from = NULL;
    dlist_iter_t src_to = NULL;
    dlist_t *listA = DLCreate(); 
    dlist_t *listB = DLCreate();

    if (NULL == listA)
    {
        return (FAIL);
    }
    if (NULL == listB)
    {
        DLDestroy(listA);
        return (FAIL);
    }
   
    for (i = 0; i < 10; ++i)
    {
        arr[i] = i; 
        DLInsertBefore(DLEnd(listA), &arr[i]);
        arr2[i] = i + 10; 
        DLInsertBefore(DLEnd(listB),&arr2[i]);        
    }
     
    src_from = DLNext(DLNext(DLBegin(listB)));
    src_to   = DLPrev(DLPrev(DLEnd(listB)));
    DLSpliceBefore(DLBegin(listA), src_from, src_to);
    src_to = DLBegin(listA);    
    while(DLEnd(listA) != src_to)
    {
        if(*(int*)DLGetData(src_to) > 10)
        {
            ++successes;
        }
        
        src_to = DLNext(src_to);
    }
    
    DLDestroy(listA);
    DLDestroy(listB);
    
    return ((6 == successes) ? (SUCCESS) : (FAIL));
}

static int TestDLCount(void)
{
    int a = 5; 
    int successes = 0; 
    dlist_t *list = DLCreate();
    
    if (NULL == list)
    {
        return (FAIL);
    }
    
    if (0 == DLCount(list))
    {
        ++successes;    
    }
    
    DLPushBack(list, &a);
    
    if (1 == DLCount(list))
    {
        ++successes; 
    }
    
    DLDestroy(list);
    
    return ((successes == 2) ? (SUCCESS) : (FAIL)); 
}

/****-----------------ACTION FUNCTIONS--------------------------------*/

static int DLFinder(void *data, void *param) /*for internal testing*/
{
    return (*(int*)param == *(int*)data);
}

 
