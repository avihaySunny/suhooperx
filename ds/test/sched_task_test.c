/*******************************************************************************
* Programmer: Avihay Asraf
* sched_task_test.c
* File: sched_task testing
* Date: 23/5/19
*******************************************************************************/
/*--------------------TEST DESCRYPTION-----------------------------------------
*               1. Tests Create task to see if exists.          
*               2. Tests IsSameTask for two different task and then for two
*                  identical tasks.
*               3. Creates a task and checks it retrieved abs_time;  
*               4. Creates a task and check created UID.    
*               5. Creates task with action and perform said action. 
*---------------------------------------------------------------------------*/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */

#include "sched_task.h"

/*----------------------------------------------------------------------------*/

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

/*----------------------------------------------------------------------------*/

#define UNUSED(a)    ((void)(a))
#define SUCCESS (0)
#define FAIL (1)

/*----------------------------------------------------------------------------*/

static int Action(void *tmp);
static int TestIsSameTask(void);
static int TestTaskCreate(void);
static int TestGetTimeToRun(void);
static int TestTaskGetUID(void);
static int TestTaskAction(void);

/*----------------------------------------------------------------------------*/

int main(void)
{
    size_t num_of_tests = 5; 
    size_t test_fail    = 0; 
    
    if (FAIL == TestTaskCreate())
    {
        puts(RED"TaskCreateTest FAIL "RESET);
        ++test_fail;
    }
    
    if (FAIL == TestIsSameTask())
    {
        puts(RED"TestIsSameTask FAIL "RESET);
        ++test_fail;
    }
    
    if (FAIL == TestGetTimeToRun())
    {
        puts(RED"TestGetTimeToRun "RESET);
        ++test_fail;
    }
    
    if (FAIL == TestTaskGetUID())
    {
        puts(RED"TestTaskGetUID FAIL "RESET);
        ++test_fail;
    } 
    
    if (FAIL == TestTaskAction())
    {
        puts(RED"TestTaskAction FAIL "RESET);
        ++test_fail;
    } 
     
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    
    return (EXIT_SUCCESS);
}

/*----------------------------------------------------------------------------*/

static int TestTaskCreate(void)
{
    void *tmp = NULL;  
    task_t *task = SchTaskCreate(60 , Action, tmp);
    if (NULL == task)
    {
        return FAIL;
    }
    
    SchTaskDestroy(task);
    task = NULL; 
    
    return SUCCESS; 
}

/*----------------------------------------------------------------------------*/

static int TestIsSameTask(void)
{
    void *tmp = NULL;  
    int fail = 0; 
    uid_type id1 = {0}; 
    uid_type id2 = {0}; 
    task_t *task1 = SchTaskCreate(60 , Action, tmp);
    task_t *task2 = NULL;  
    if (NULL == task1)
    {
        return FAIL; 
    }
    
    task2 = SchTaskCreate(60 , Action, tmp);
    
    if (NULL == task2)
    {
        SchTaskDestroy(task1);
    }
    
    id1 = SchTaskGetUID(task1);
    id2 = SchTaskGetUID(task2); 
    
    fail = SchIsSameTask((const task_t*)task1, &id1) +         
           SchIsSameTask((const task_t*)task1, &id2);
           
    SchTaskDestroy(task1);
    SchTaskDestroy(task2);
    UNUSED(tmp);
    
    return ((1 == fail) ? (SUCCESS) : (FAIL));     
}

/*----------------------------------------------------------------------------*/

static int TestGetTimeToRun(void)
{
    void *tmp = NULL;  
    int fail = 0; 
    task_t *task1 = SchTaskCreate(60 , Action, tmp);
    task_t *task2 = NULL;  
    if (NULL == task1)
    {
        return FAIL; 
    }
    
    task2 = SchTaskCreate(60 , Action, tmp);
    
    if (NULL == task2)
    {
        SchTaskDestroy(task1);
    }
    if ((SchTaskGetTimeToRun(task1) > 0 ) &&
        (SchTaskGetTimeToRun(task2) > 0))
    {
        fail = 1;
    }
    
    SchTaskDestroy(task1);
    SchTaskDestroy(task2);
    UNUSED(tmp);
    
    return ((fail == 1) ? (SUCCESS) : (FAIL));  
}

/*----------------------------------------------------------------------------*/

static int TestTaskGetUID(void)
{
    void *tmp = NULL;  
    int fail = 0; 
   
    task_t *task = SchTaskCreate(60 , Action, tmp); 
    if (NULL == task)
    {
        return FAIL; 
    }
    
    ((UIDIsBad(SchTaskGetUID(task)) == 0) ? (fail = 0) : (fail = 1)); 
    SchTaskDestroy(task);
    UNUSED(tmp);
    
    return fail;  
}

static int TestTaskAction(void)
{
    int param = 5;   
    int fail = 0; 
   
    task_t *task = SchTaskCreate(60 , Action, &param); 
    if (NULL == task)
    {
        return FAIL; 
    }
    
    if (param !=  SchTaskRunTask(task))
    {
        ++fail;
    }
    
    SchTaskDestroy(task);
    
    return ((fail == 0) ? (SUCCESS) : (FAIL));
}

/*----------------------------------------------------------------------------*/

static int Action(void *tmp)
{ 
    assert(tmp);
    return (*(int*)tmp);
}

