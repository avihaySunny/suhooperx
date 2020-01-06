/*******************************************************************************
* Programmer: Avihay Asraf
* sorted_test.c
* File: sorted testing
* Date: ב' מאי 20 16:51:38 IDT 2019
*******************************************************************************/
/*--------------------TEST DESCRYPTION-----------------------------------------
*               1. Tests IsEmpty on empty and unempty list         
*               2. Tests Merging sorted lists 
*               3. Tests insert in right order 
*               4. Test erasing nodes from list 
*               5. Tests Find (uses ForEach) and looks for data in list and for
*                  data not on the list, checks for correct returns;
*               6. Tests count on empty list and on unempty list.  
*------------------------------------------------------------------------------*/
#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf  puts                             */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcmp                                   */

#include "./include/sorted.h"
                /*--- Color Scheme----*/
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

/*-----------------------------------------------------------------------------*/
static int  StrIsBefore(const void *left, const void *right);
static int CmpData(const void *dataA, const void *dataB); 
static int TestMergeLists(void); 
static int TestSortedListEmpty(void);
static int TestSortedInsert(void); 
static int TestErase(void); 
static int Find(const void *data,const void *param); 
static int TestSortedFind(void);
static int TestSortedCount(void);

/*------------------------------MAIN--------------------------------------------*/
int main(void)
{
    size_t num_of_tests = 6; 
    size_t test_fail = 0; 
   
    if (FAIL == TestSortedListEmpty())
    {
        puts(RED"SortedListIsEmpty Test Fail"RESET);
        ++test_fail;
    }

    if (FAIL == TestSortedInsert())
    {
        puts(RED"Insert Test failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestErase())
    {
        puts(RED"Erase Test failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestSortedCount())
    {
        puts(RED"Count Test failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestSortedFind())
    {
        puts(RED"Find Test failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestMergeLists())
    {
        puts(RED"Merge lists Test failed"RESET);
        ++test_fail;
    }
    
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    return (EXIT_SUCCESS);
}

/*---------------------------TEST-FUNCTIONS--------------------------------*/
static int TestMergeLists(void)
{   
    unsigned int i = 0;
    int max = 0;  
    static int arr1[16] = {0};
    static int arr2[16] = {0};  
    
    slist_t *listA = SortedListCreate(CmpData);
    slist_t *listB = SortedListCreate(CmpData);
    if (NULL == listA)
    {
        return FAIL;
    }
    if (NULL == listB)
    {   
        SortedListDestroy(listA);
        
        return FAIL;
    }

    for (i = 0; i < 4; ++i)
    {
        arr1[i] = rand() % 15;  
        SortedListInsert(listA, &arr1[i]);  
    }
    
    for (i = 0; i < 7; ++i)
    {
         arr2[i] = rand () % 37;  
        SortedListInsert(listB, &arr2[i]); 
    }
    
    SortedListMerge(listA, listB);
    max = *(int*)SortedListPopBack(listA);
    for (i = 0; i < SortedListCount(listA); ++i)
    {
        if (*(int*)SortedListPopFront(listA) > max)
        {
            SortedListDestroy(listA);
            SortedListDestroy(listB);
            
            return FAIL; 
        }
    }
    
    SortedListDestroy(listA);
    SortedListDestroy(listB);
  
    return (SUCCESS);
}
/*------------------------------------------------------------------------------*/
static int TestSortedListEmpty(void)
{ 
    unsigned int successes = 0; 
    
    slist_t *list = SortedListCreate(CmpData);
    if (NULL == list)
    {
        return FAIL;
    }
    
    if (NULL == list)
    {
        return (FAIL);
    }  
    
    if (1 == SortedListIsEmpty(list))
    {
        ++successes;  
    }
    
    SortedListInsert(list, &successes);
    if(0 == SortedListIsEmpty(list))
    {
        ++successes;
    }
    
    SortedListDestroy(list); 
    
    return ((2 == successes) ? (SUCCESS) : (FAIL));
}
/*-----------------------------------------------------------------------------*/
static int TestSortedInsert(void)
{
    unsigned int i = 0;
    int max = 0;  
    static int arr1[10] = {0};
    slist_t *list = SortedListCreate(CmpData);
    if (NULL == list)
    {
        return FAIL;
    }
    
    for (i = 0; i < 10; ++i)
    {
        arr1[i] = rand() % 10;  
        SortedListInsert(list, &arr1[i]);    
    }    
     
    max  = *(int*)SortedListPopBack(list); 
    
    for (i = 0; i < SortedListCount(list); ++i)
    {
        if (*(int*)SortedListPopFront(list) > max)
        {
            SortedListDestroy(list);
            
            return FAIL; 
        }
    }
    
    SortedListDestroy(list); 
    
    return SUCCESS;   
}
/*----------------------------------------------------------------------------*/

static int TestSortedFind(void)
{
    int i = 0;
    char st[][10] = {"hello", "world", "my", "name", "is", "ben"};
    int successes = 0; 
    slist_t *slist = SortedListCreate(StrIsBefore);
    if (NULL == slist)
    {
        puts("Malloc failur");
        
        return FAIL;
    } 
    
    for (i = 0; i < STRSIZE; ++i)
    {
        if (0 != strcmp((char *)SortedListGetData(
                         SortedListInsert(slist, st[i])), st[i]))
        {
            ++successes;
           
        }
        
        if ((size_t)(i + 1) != SortedListCount(slist))
        {
            ++successes; 
         
        }
    }

    if (0 != SortedListIsBadIterator((const slist_t*)slist, 
                 (const slist_iter_t)SortedListFind(slist, Find, (const void *)st[1])))
    {
        ++successes; 
        
    }
    
    if(!SortedListIsSameIterator((const slist_iter_t)SortedListFind(slist, Find, 
                                 (const void *)st[1]), (const slist_iter_t)
                                  SortedListPrev(SortedListEnd(slist))))
    {
        ++successes; 
        
    }
    
    for (i = 0; i < STRSIZE; ++i)
    {
        SortedListPopBack(slist);
                
        if ((size_t)(STRSIZE - i - 1) != SortedListCount(slist))
        {
            ++successes; 
       
        }
    }
    
    SortedListDestroy(slist);
    slist = NULL;
    
    return (!(successes == 0));   
}
/*------------------------------------------------------------------------------*/

static int TestErase(void)
{
    unsigned int i = 0;
    int successes = 0;
    static int arr1[10] = {0};
    
    slist_t *list = SortedListCreate(CmpData);
    if (NULL == list)
    {
        return FAIL;
    }
    
    if (0 == SortedListCount(list))
    {
        ++successes;
    }
    for (i = 0; i < 10; ++i)
    {
        arr1[i] = rand() % 10;  
        SortedListInsert(list, &arr1[i]);    
    }    
    
    if (10 == SortedListCount(list))
    {
        ++successes;
    }
    
    for (i = 0; i < 4; ++i)
    {    
        SortedListErase(SortedListBegin(list));
    }    
    
    if (6 == SortedListCount(list))
    {
        ++successes; 
    }
    
    SortedListDestroy(list); 
    
    return ((3 == successes) ? (SUCCESS) : (FAIL));
}
/*-----------------------------------------------------------------------------*/

static int TestSortedCount(void)
{
    int a = 5; 
    int successes = 0; 
    
    slist_t *list = SortedListCreate(CmpData);
    if (NULL == list)
    {
        return (FAIL);
    }
    
    if (0 == SortedListCount(list))
    {
        ++successes;    
    }
    
    SortedListInsert(list, &a);
    
    if (1 == SortedListCount(list))
    {
        ++successes; 
    }
    
    SortedListDestroy(list);
    
    return ((successes == 2) ? (SUCCESS) : (FAIL)); 
}
/*-----------------------------------------------------------------------------*/

static int CmpData(const void *dataA, const void *dataB)
{
    assert(dataA);
    assert(dataB); 
    
    return (*(int*)dataA > *(int*)dataB);   
}
/*-----------------------------------------------------------------------------*/

static int StrIsBefore(const void *left, const void *right)
{
    if (0 < strcmp((char *)left, (char *)right))
    {
        return 1;
    } 
    
    return 0;
}
/*-----------------------------------------------------------------------------*/

static int Find(const void *data,const void *param) /*for internal testing*/
{
    return (*(int*)param == *(int*)data);
}
/*-----------------------------------------------------------------------------*/



