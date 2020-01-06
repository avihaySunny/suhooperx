/*******************************************************************************
* Programmer: Avihay Asraf
* queue_test.c
* File: queue testing
* Date: ה' מאי 16 09:59:10 IDT 2019
*******************************************************************************/
/*--------------------TEST DESCRYPTION-----------------------------------------
*               1. Tests Creating a queue and destroys it.          
*               2. Appends to queues and checks to see if apennded properly. 
*                  
*               3. Adds to queue and checks if added and added correctly. 
*               4. Remove from queue and checks removal.  
*               5. Tests destroying empty queue. 
*-----------------------------------------------------------------------------*/

#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE                */ 
#include "./include/queue.h"

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"
/*----------------------------------------------------------------------------*/
static int TestQAppend(void);
static int TestIsEmpty(void); 
static int TestQEnqueue(void);
static int TestQDequeue(void);
static int TestDestroyEmptyQueue(void);

/*************************TESTING**********************************************/
int main(void)
{   
    size_t num_of_tests = 5; 
    size_t test_fail = 0; 
    
    if (0 == TestDestroyEmptyQueue())
    {
        puts(RED"Empty Queue destroy Test Fail");
        ++test_fail;
    }

    if (0 == TestIsEmpty())
    {
        puts(RED"Empty Queue Test Fail");
        ++test_fail;
    }
    
    if (0 == TestQAppend())
    {
        puts(RED"Queue Append Test Fail");
        ++test_fail;
    }
    
    if (0 == TestQEnqueue())
    {
        puts(RED"Add to Queue Test Fail");
        ++test_fail;
    } 
    
    if (0 == TestQDequeue())
    {
        puts(RED"Remove From Queue Test Fail");
        ++test_fail;
    }
    
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    return (EXIT_SUCCESS);
}

static int TestDestroyEmptyQueue(void)
{
    queue_t *empty = QCreate();
    if (NULL == empty)
    {
        return (0);
    }
    QDestroy(empty);
    return (1);
}

static int TestIsEmpty(void)
{
    queue_t *q1 = QCreate(); 
    if (NULL == q1)
    {
        return (0);
    }
    if (QIsEmpty(q1)) /*should be empty*/
    {
        QDestroy(q1); 
        return (1);
    }
    
    QDestroy(q1);
    return (0);
}

static int TestQAppend(void)
{
    static int arr[50]; 
    size_t i = 0; 
    queue_t *q1 = NULL; 
    queue_t *q2 = NULL; 
    int err = 1; 
    
    q1 = QCreate(); 
    if (NULL == q1)
    {
        return (0); 
    } 
    
    q2 = QCreate();
    if (NULL == q2)
    {
        free(q1);
        return (0); 
    }
    
    for (i = 0; i < 30; ++i)
    {
        arr[i] = i; 
    }
    
    for (i = 0; i < 8; ++i)
    {
        QEnqueue(q1, &arr[i]);  
        QEnqueue(q2, &arr[i+8]);
    }
   
    QAppend(q1,q2); 
    for (i = 0; i < 15; ++i)
    {
        if (arr[i] != *(int*)QDequeue(q1))
        {
            err = 0;
            QDestroy(q1);
        }
    }
    
    QDestroy(q1); 
    return (err);
}

static int TestQEnqueue(void)
{
    int i = 0; 
    static int arr [25];
    queue_t *q1 = QCreate(); 
    
    if (NULL == q1)
    {
        return (0); 
    }
    
    for (i = 0; i < 15; ++i)
    {
        arr[i] = i; 
        QEnqueue(q1, &arr[i]);
    }
    
    if (QCount(q1) == 15)
    {
        QDestroy(q1);
   
        return (1);
    }
    
    QDestroy(q1);
   
    return (0);
}

static int TestQDequeue(void)
{
    int i = 0; 
    static int arr [25];
    queue_t *q1 = QCreate(); 
    
    if (NULL == q1)
    {
        return (0); 
    }
    
    for (i = 0; i < 15; ++i)
    {
        arr[i] = i; 
        QEnqueue(q1, &arr[i]);
    }
    
    for (i = 0; i < 5; ++i)
    {
        QDequeue(q1);
    }
   
    if (10 == QCount(q1))
    {
        QDestroy(q1);
        
        return (1);
    }   
    
    QDestroy(q1);
    
    return (0);
}


