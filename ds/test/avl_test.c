/*******************************************************************************
* Programmer: Avihay Asraf
* avl_test.c
* File: avl testing
* Date: ב' יונ 17 10:37:01 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include "avl.h"

#define UNUSED(a)   ((void)(a))
#define TESTSIZE (1500) 
#define RANGE (3000)

/* ------------------------------TESTS---------------------------------------- */

static void TestCreateDestroy(void);
static void TestInsertRemove(void);
static void TestSizeFind(void);
static void IntegrationTest(void);
/* ---------------------------------------------------------------------------- */

static int CmpData(const void *dataA, const void *dataB);
static int CmpInt(const int *dataA,const int *dataB); 
static void FillRandomArr(int *arr, size_t size); 
static int IsBFValid(ssize_t balance_factor);

/* --------------------------------MAIN ---------------------------------------- */
int main(void)
{
    TestCreateDestroy();
    TestInsertRemove();
    TestSizeFind();  
    IntegrationTest();  
    
    return (EXIT_SUCCESS);
}
/* ------------------------------------------------------------------------------ */
static int CmpData(const void *dataA, const void *dataB)
{   
    assert(dataA && dataB);
    
    return (CmpInt(dataA, dataB));
}   
/* ------------------------------------------------------------------------------ */
static int CmpInt(const int *dataA,const int *dataB)
{
    return (*dataA - *dataB); 
}
/* ------------------------------------------------------------------------------ */
int Print(const void *dataA, void *dataB)
{
    printf(": %d\n", *(int *)dataA);
    UNUSED(dataB);

    return 0;
}
/* ------------------------------------------------------------------------------ */
static void TestCreateDestroy(void)
{
    avl_t *tree = AVLCreate(CmpData); 
    if (NULL == tree)
    {
        puts("Failed to create tree");
    }

    if (!AVLIsEmpty(tree))
    {
        puts("Avl creates not empty tree");
    }

    AVLDestroy(tree);
    tree = NULL;
}
/* ------------------------------------------------------------------------------ */
static void TestInsertRemove(void)
{
    int arr[]   = {10, 8, 5, 12, 4, 6}; 
    size_t i = 0;
    size_t size = sizeof(arr)/sizeof(arr[0]);
    avl_t *tree = AVLCreate(CmpData); 
    if (NULL == tree)
    {
        puts("Failed to create tree");
    }

    if (!AVLIsEmpty(tree))
    {
        puts("Avl creates not empty tree");
    }

    if (0 != AVLInsert(tree, arr))
    {
        puts("Insert failed");
    }
    if (0 != AVLHeight(tree))
    {
        puts("Height of tree is not 0");
    }
    if (AVLIsEmpty(tree))
    {
        puts("Avl empty after insert");
    }
    AVLRemove(tree, arr);

    if (!AVLIsEmpty(tree))
    {
        puts("Avl not empty after remove");
    }

    for (i = 0; i < size; i++)
    {
        if (0 != AVLInsert(tree, arr + i))
        {
            puts("Insert failed");
        }
    }

    if (2 != AVLHeight(tree))
    {
        puts("Height of tree is not 3");
    }
    
    AVLDestroy(tree);
    tree = NULL;
}
/* ------------------------------------------------------------------------------ */
static void TestSizeFind(void)
{
    int arr[]   = {10, 8, 5, 12, 4, 6,}; 
    size_t i = 0;
    size_t size = sizeof(arr)/sizeof(arr[0]);
    avl_t *tree = AVLCreate(CmpData); 
    if (NULL == tree)
    {
        puts("Failed to create tree");
    }

    if (!AVLIsEmpty(tree))
    {
        puts("Avl creates not empty tree");
    }

    if (0 != AVLSize(tree))
    {
        puts("Avl size not 0 on create");
    }

    if (0 != AVLInsert(tree, arr))
    {
        puts("Insert failed");
    }
    if (0 != AVLHeight(tree))
    {
        puts("Height of tree is not 0");
    }
    if (AVLIsEmpty(tree))
    {
        puts("Avl empty after insert");
    }

    if (1 != AVLSize(tree))
    {
        puts("Avl size not grow after insert");
    }

    AVLRemove(tree, AVLFind(tree, arr));

    if (0 != AVLSize(tree))
    {
        puts("Avl size not shrink after remove");
    }

    if (!AVLIsEmpty(tree))
    {
        puts("Avl not empty after remove");
    }

    for (i = 0; i < size; i++)
    {
        if (0 != AVLInsert(tree, arr + i))
        {
            puts("Insert failed");
        }
    }

    if (size != AVLSize(tree))
    {
        puts("Avl size not grow after insert");
    }

    if (0 != CmpData(arr + 3, AVLFind(tree, arr + 3)))
    {
        puts("Find does not work");
    }

    AVLDestroy(tree);
    tree = NULL;
}
/* ------------------------------------------------------------------------------ */
static void IntegrationTest(void)
{
    int arr[TESTSIZE] = {0}; 
    size_t i = 0; 
    int fails = 0; 
    avl_t *tree = AVLCreate(CmpData); 

    FillRandomArr(arr, TESTSIZE); 

    for (i = 0; i < TESTSIZE; ++i)
    {
        AVLInsert(tree, &arr[i]); 
        if (!IsBFValid(AVLGetBF(tree)))
        {
            ++fails;
        }
    }

    if (TESTSIZE != AVLSize(tree))
    {
        puts("Error Inserting from array"); 
    }

    for (i = 10; i < 35; ++i)
    {
        AVLRemove(tree, &arr[i]);
        if (!IsBFValid(AVLGetBF(tree)))
        {
            ++fails;
        }

    }

    if (TESTSIZE - 25 != AVLSize(tree))
    {
        puts("Error Removing / Finding"); 
    }

    if (0 != fails)
    {
        puts ("Error balancing "); 
    }

    AVLDestroy(tree);
    
}
/* ------------------------------------------------------------------------------ */
static void FillRandomArr(int *arr, size_t size)
{
    int histogram[RANGE] = {0}; 
    size_t i = 0; 
    int tmp = 0; 
    while ( i < size)
    {
        tmp = rand() % RANGE;
        if(histogram[tmp] == 0)
        {
            arr[i] = tmp; 
            ++i; 
            histogram[tmp] = 1; 
        } 
    }
}

/* ------------------------------------------------------------------------------ */
static int IsBFValid(ssize_t balance_factor)
{
    if (balance_factor < -1 || balance_factor > 1)
    {
        return 0; 
    }

    return 1; 
}
