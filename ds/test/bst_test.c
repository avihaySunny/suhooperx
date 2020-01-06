/*******************************************************************************
* Programmer: Avihay Asraf
* bst_test.c
* File: bst testing
* Date: ג' יונ 11 12:56:52 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf puts                              */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE                */

#include "bst.h"
#define BIGSIZE (1000)
/*---------------------------------------------------------------------------- */
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define FAIL (1)
#define SUCCESS (0)
/*---------------------HelperFunctions----------------------------------------*/
static int CmpData(const void *dataA, const void *dataB);
static int CmpInt(const int *dataA,const int *dataB); 
static int InArray(int *arr, int size, int num);

/*------------------TestFunctions---------------------------------------------*/ 
/* Creates, checks not empty, destroy  */
static int TestCreateDestroy(void); 

/*  Inserts elements into tree, searches for them and compares to input data */
static int InsertAndFindTest(void);

/*builds a tree using disordered array, runs from begining to end and visa versa
* and compares to sorted array to check In Order travelsal*/
static int TestTraverseInOrder(void);

/* Creates a big tree and fills it, checks data, removes everything - repeat*/
static int IntegrationTest(void);
/*------------------------------------------------------------------------------*/
int main(void)
{
    size_t num_of_tests = 4; 
    size_t test_fails    = 0; 

    if (FAIL == TestCreateDestroy())
    {
        puts(RED"Insert And Find Failed\n"RESET);
        ++test_fails; 
    }  

    if (FAIL == InsertAndFindTest())
    {
        puts(RED"Insert And Find Failed\n"RESET); 
        ++test_fails; 
    }
    
    if (FAIL == TestTraverseInOrder())
    {
        puts(RED"Traverse Test Fail\n"RESET);
    }   

    if (FAIL == IntegrationTest())
    {
        puts(RED"Integration Test Fail\n"RESET);
    }
   
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fails); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fails);

    return (EXIT_SUCCESS);
}

static int CmpData(const void *dataA, const void *dataB)
{   
    assert(dataA && dataB);
    
    return (CmpInt(dataA, dataB));
}

static int CmpInt(const int *dataA,const int *dataB)
{
    return (*dataA - *dataB); 
}

static int InsertAndFindTest(void)
{
    int i = 0, fails = 0; 
    static int arr[] = {150, 140, 160, 135, 155, 120, 123, 112, 90, 175, 180, 190, 115, 210};
    iter_t iter_arr[13] = {NULL};
    
    bst_t *tree = BSTCreate(CmpData); 
    if (NULL == tree )
    {
        return FAIL; 
    }

    if (1 != BSTIsEmpty(tree))
    {
        ++fails; 
    }
    
    for (i = 0; i < 13; ++i)
    {
        iter_arr[i] = BSTInsert(tree, &arr[i]);
        printf("%d\n", arr[i]);
    }

    if (0 != BSTIsEmpty(tree))
    {
        ++fails; 
    }

    for (i = 0; i < 13; ++i)
    {
        if (arr[i] != (*(int*)BSTGetData(iter_arr[i])))
        {
            ++fails; 
        }

        if (iter_arr[i] != BSTFind(tree, &arr[i]))
        {
            ++fails;
        }

        if (NULL != BSTFind(tree, &arr[13]))
        {
            ++fails;
        }
    }  

    BSTDestroy(tree);
    
    return ((fails == 0 ) ? (SUCCESS) : (FAIL));
}

static int TestCreateDestroy(void)
{
    int fails = 0; 
    int a = 10; 
    bst_t *tree = BSTCreate(CmpData); 
    if (NULL == tree)
    {
        return FAIL; 
    }

    if (1 != BSTIsEmpty(tree))
    {
        ++fails;
    }

    BSTInsert(tree, &a); 

    if (0 != BSTIsEmpty(tree))
    {
        ++fails;
    }

    BSTDestroy(tree); 
    
    return ((fails == 0) ? (SUCCESS) : (FAIL)); 

}

static int TestTraverseInOrder(void)
{
    int i = 0, fails = 0; 
    int arr[] = {150, 140, 160, 135, 155, 120, 123, 112, 90, 175, 180, 190, 115};
    int sorted_arr[] = {90, 112, 115, 120, 123, 135, 140, 150, 155, 160, 175, 180, 190};
    iter_t iter = NULL; 
    bst_t *tree = BSTCreate(CmpData); 
    
    if (NULL == tree)
    {
        return FAIL; 
    }

    for (i = 0; i < 13; ++i)
    {
        BSTInsert(tree, &arr[i]);
    }

    iter = BSTBegin(tree); 
    for (i = 0; i <13; ++i)
    {
        if (*(int*)BSTGetData(iter) != sorted_arr[i])
        {
            ++fails;
        }

        iter = BSTNext(iter);
    }

    iter = BSTPrev(BSTEnd(tree));
    for (i = 12; i >= 0; --i)
    {
        if (*(int*)BSTGetData(iter) != sorted_arr[i])
        {
            ++fails;
        }
        
        iter = BSTPrev(iter);
    }

    BSTDestroy(tree);  

    return (fails == 0) ? (SUCCESS) : (FAIL);
}

static int IntegrationTest(void)
{
    iter_t iter = NULL;
    int arr[BIGSIZE] = {0};
    int i = 0;
    int rnd = 0;
    int fails = 0; 
    bst_t *tree = BSTCreate(CmpData);
    if (NULL == tree)
    {
        puts("Create");
    }

    arr[0] = 1500;
    for (i = 1; i < BIGSIZE;)
    {
        rnd = rand() % 10000;
        if (!InArray(arr, BIGSIZE, rnd))
        {
            arr[i] = rnd;
            ++i;
        }
    }

    if (!BSTIsEmpty(tree))
    {
        ++fails;
    }

    for (i = 0; i < BIGSIZE; i++)
    {
        if (BSTSize(tree) != (size_t)i)
        {
            ++fails;
        }

        iter = BSTInsert(tree, &arr[i]);
        if (0 != CmpData(BSTGetData(iter), &arr[i]))
        {
            ++fails;
        }
    }

    if (BSTIsEmpty(tree))
    {
        ++fails;
    }

     for (iter = BSTBegin(tree), i = BIGSIZE; iter != BSTEnd(tree); --i, iter = BSTBegin(tree))
    {
        if (BSTSize(tree) != (size_t)i)
        {
            ++fails;
        }

        if (0 != CmpData(BSTRemove(iter), BSTGetData(iter)))
        {
            ++fails;
        }
    }

    if (!BSTIsEmpty(tree))
    {
        ++fails;
    }

    for (i = 0; i < BIGSIZE; i++)
    {
        iter = BSTInsert(tree, &arr[i]);
        if (0 != CmpData(BSTGetData(iter), &arr[i]))
        {
            ++fails;
        }
    }
    
    for (i = BIGSIZE - 1; i >= 0; --i)
    {
        if (0 != CmpData(BSTRemove(BSTFind(tree, &arr[i])), &arr[i]))
        {
            ++fails;
        }
    } 

    BSTDestroy(tree);
    tree = NULL;
    
    return ((fails == 0) ? (SUCCESS) : (FAIL));
}

static int InArray(int *arr, int size, int num)
{
    int i = 0;

    for (i = 0; i < size; i++)
    {
        if (arr[i] == num)
        {
            return 1;
        }
    }
    
    return 0;
}

