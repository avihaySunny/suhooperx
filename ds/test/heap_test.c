/*******************************************************************************
* Programmer: Avihay Asraf
* heap_test.c
* File: heap testing
* Date: ב' יונ 24 15:26:50 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include "heap.h"

static void TestCreateDestroy(void);
int CmpData(const void *dataA, const void *dataB);
int CmpDataInt(const int *dataA,const  int *dataB);
static int IsMatch(const void *data, const void *dataB);
static int IsMatchInt(const int *dataA, const int *dataB);


typedef struct student
{
    char name[50]; 
    size_t age; 
    int id; 

} stu_t; 


static int CmpStudent(const void *studentA, const void *studentB);
static int CmpStudentID(const stu_t *studentA,const stu_t *studentB);
static void TestATrivialInsert(void);
static void TestHeapInsert(void);
static void TestHeapRemove(void);
static int IsMatchStudent(const void *dataA, const void *dataB);
static void TestHeapTrivialRemove(void);
static void TestHeapPop(void);

static stu_t students[] =   {{"frank"  , 20, 1000   }, 
                            {"frankosh", 25, 1001   }, 
                            {"frakish", 21, 1002    },
                            {"frankolo", 27, 1003   },
                            {"frakeyla", 26, 1004   },
                            {"frakoshov", 22, 1005  },
                            {"frankoski", 20, 1006  },
                            {"mistyfranks", 29, 1007},
                            {"walkmyway", 21, 1008  },
                            {"andbegintoplay", 24, 1009},
                            {"frakoshish", 26, 1010}};

#define STUDENT_SIZE (sizeof(students)/ sizeof(students[0]))

int main(void)
{
    TestCreateDestroy();
    TestATrivialInsert();
    TestHeapInsert();
    TestHeapTrivialRemove(); 
    TestHeapRemove();
    TestHeapPop();

    return (EXIT_SUCCESS);
}


static void TestCreateDestroy(void)
{
    heap_t *heap = HEAPCreate(CmpData); 
    if (NULL == heap)
    {
        puts("Create failed"); 
    }

    if (!HEAPIsEmpty(heap))
    {
        puts("Create failed Is empty"); 
    }

    HEAPDestroy(heap);
}

static void TestATrivialInsert(void)
{
    heap_t *heap = HEAPCreate(CmpStudent);
    if (!HEAPIsEmpty(heap))
    {
        puts ("fail line 171");
    }
    HEAPInsert(heap, &students[0]);

    if (&students[0] != HEAPPeek(heap))
    {
        puts ("fail line 177");
    }

    HEAPDestroy(heap);
}

static void TestHeapInsert(void)
{
    heap_t *heap = HEAPCreate(CmpStudent);
    int i = 0; 

    if (!HEAPIsEmpty(heap))
    {
        puts ("fail line 188");
    }

    for (i = 0; i < (int)STUDENT_SIZE; ++i)
    {
        if (-1 == HEAPInsert(heap, &students[i]))
        {
            puts("Insertation Error line 178");
        }
    }

    for (i = STUDENT_SIZE - 1; i > 0; --i)
    {
        if (!IsMatchStudent(&students[i],HEAPPeek(heap)))
        {
            puts ("Insertion Error line 184");
        }

        HEAPPop(heap);
    }

    HEAPDestroy(heap);
}

static void TestHeapRemove(void)
{
    heap_t *heap = HEAPCreate(CmpData);
    int arr[] = {1, 5, 4, 7, 12, 19}; 
    int remove_arr[] = {19, 12, 7, 4, 5, 1}; 
    size_t size = sizeof(arr)/sizeof(arr[0]);
    size_t i = 0; 
    
    if (!HEAPIsEmpty(heap))
    {
        puts ("fail line 188");
    }

    for (i = 0; i < size; ++i)
    {
        if (-1 == HEAPInsert(heap, &arr[i]))
        {
            puts("Insertation Error line 178");
        }
    }

    for (i = 0; i < size; ++i)
    {
        HEAPRemove(heap, &remove_arr[i], IsMatch); 
        HEAPRemove(heap, &remove_arr[i], IsMatch);
    }

    if (!HEAPIsEmpty(heap))
    {
        puts ("error line 196");
    }

    HEAPDestroy(heap);
}

static void TestHeapTrivialRemove(void)
{
    heap_t *heap = HEAPCreate(CmpData);
    int arr[] = {1}; 
    int found = 1; 
    
    HEAPInsert(heap, &arr[0]);
    HEAPRemove(heap, &found, IsMatch); 
    HEAPDestroy(heap);
}

static void TestHeapPop(void)
{
    heap_t *heap = HEAPCreate(CmpData);
    int arr[] = {1, 5, 4, 6, 9, 11, 7, 14, 8, 21};
    int sort_arr[] = {21, 14, 11, 9, 8, 7, 6, 5, 4, 1};
    size_t size = sizeof(arr)/sizeof(arr[0]);
    size_t i = 0; 

    for (i = 0; i < size; ++i)
    {
        HEAPInsert(heap, &arr[i]);
    }
    
    i = 0; 

    while(!HEAPIsEmpty(heap))
    {
        if (!IsMatch(&sort_arr[i], HEAPPeek(heap)))
        {
            puts("error removing");
        }

        HEAPPop(heap); 
        ++i; 
    }
    
    HEAPDestroy(heap);
}

int CmpData(const void *dataA, const void *dataB)
{
    return(CmpDataInt(dataA, dataB));
}

int CmpDataInt(const int *dataA, const int *dataB)
{
    return (*dataA > *dataB);
}

static int IsMatch(const void *dataA, const void *dataB)
{
    return IsMatchInt(dataA, dataB);
}


static int IsMatchInt(const int *dataA, const int *dataB)
{
    return (*dataA == *dataB);
}

static int CmpStudent(const void *studentA, const void *studentB)
{
    return CmpStudentID(studentA, studentB);
}

static int CmpStudentID(const stu_t *studentA,const stu_t *studentB)
{
    return (studentA->id > studentB->id);
}

static int IsMatchStudent(const void *dataA, const void *dataB)
{
    const stu_t *a = dataA; 
    const stu_t *b = dataB;

    return (a->id == b->id); 
}
