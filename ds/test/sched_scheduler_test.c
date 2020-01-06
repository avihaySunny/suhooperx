/*******************************************************************************
* Programmer: Avihay Asraf
* sched_scheduler_test.c
* File: sched_scheduler testing
* Date: '23/5/19
*******************************************************************************/
/*--------------------UNIT TEST DESCRYPTION-----------------------------------------
*               1. Tests Create scheduler and checks if empty and count 
*                  is zero.           
*               2. Add 50 tasks to scheduler and then removes all 50. 
*               3. Runs a scheduler, stops, Restart scheduler.  
*               4. uses a function that return rerun status and checks it ran *                  again   
*---------------------------------------------------------------------------*/
#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE                */

#include "sched_scheduler.h" 

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define UNUSED(a)    ((void)(a))
#define SUCCESS (0)
#define FAIL (1)

/*---------------------------------------------------------------------------*/
static int TestSchCreate(void);
static int TestSchRunStop(void);
static int TestRerunTask(void);
static int TestSchAddRemove(void);

static int Action1(void *param);
static int Action2(void *param);
static int StopFunc(void *param);
static int ActionReRun(void *param);

/*---------------------------------------------------------------------------*/

int main(void)
{
    size_t num_of_tests = 4; 
    size_t test_fail    = 0; 
    
  
    if (FAIL == TestSchCreate())
    {
        puts(RED"Sch Create Failed"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestSchAddRemove())
    {
        puts(RED"Sch Add and Remove Test Failed"RESET);
        ++test_fail;
    }
     
    if (FAIL == TestSchRunStop())
    {
        puts(RED"Sch Run and Stop Fail"RESET);
        ++test_fail;
    }
    
    if (FAIL == TestRerunTask())
    {
        puts(RED"Sch Rerun task Test Failed"RESET);
        ++test_fail;
    }
    
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    return (EXIT_SUCCESS);
}
/*---------------------------------------------------------------------------*/
static int TestSchCreate(void)
{
    int is_empty = 0; 
    size_t count = 0; 
    
    sch_t *sch = SchCreate(); 
    if (NULL == sch)
    {
        return FAIL;
    } 
    
    is_empty = SchIsEmpty(sch); 
    count = SchSize(sch); 
    SchDestroy(sch);
    
    if (1 == is_empty + count )
    {
        return SUCCESS;    
    }
    
    return FAIL; 
}
/*---------------------------------------------------------------------------*/

static int TestSchAddRemove(void)
{
    uid_type ids[50] = {0}; 
    int i = 0, interval = 3;
    size_t count = 0; 
    sch_t *sch = SchCreate(); 
    if (NULL == sch)
    {
        return FAIL;
    }
    
    for (i = 0; i < 50; ++i)
    {
        ids[i] = SchAdd(sch , Action1, &interval, interval);
    }
    
     ((50 == SchSize(sch)) ? (++count) : (0));
    
    for (i = 0; i < 50; ++i)
    {
        SchRemove(sch, ids[i]); 
    }
   
    ((0 == SchSize(sch)) ? (++count) : (0));
    SchDestroy(sch);

    return ((2 == count) ? (SUCCESS) : (FAIL));

}

/*---------------------------------------------------------------------------*/
static int TestSchRunStop(void)
{
    size_t count = 0; 
    int fails = 0; 
    int i = 0; 
    int interval = 2; 
    
    sch_t *sch = SchCreate(); 
    if (NULL == sch)
    {
        return FAIL; 
    }
   
    for (i = 0; i < 5; ++i)
    {
        SchAdd(sch, Action1, &interval, interval + 1 );
    }
    
    SchAdd(sch, StopFunc, sch ,interval + 2);
    
    for (i = 0; i < 5; ++i)
    {
        SchAdd(sch, Action2, &interval,  interval + 3);
    }
    
    count = SchSize(sch);
    ((11 == count) ? (0) : (++fails));
    SchRun(sch);
    
    count = SchSize(sch);
    ((5 == count) ? (0) : (++fails));
    SchRun(sch); 
    
    count = SchSize(sch);
    ((0 == count) ? (0) : (++fails));
    SchDestroy(sch);

    return ((0 == fails) ? (SUCCESS) : (FAIL));
}

static int TestRerunTask(void)
{
    int interval = 1;
    size_t count = 0; 
    sch_t *sch = SchCreate(); 
    if (NULL == sch)
    {
        return FAIL; 
    }
    
    SchAdd(sch, ActionReRun, &interval, interval);
    SchAdd(sch, StopFunc, sch, 4);
    SchRun(sch);
    count = SchSize(sch);
    SchDestroy(sch);    
    
    return ((1 == count) ? (SUCCESS) : (FAIL));
    
}
/*---------------------------------------------------------------------------*/
static int Action1(void *param)
{
    UNUSED(param);
    
    return (1);
}
/*---------------------------------------------------------------------------*/
static int Action2(void *param)
{ 
    UNUSED(param);
    
    return (1);
}

static int ActionReRun(void *param)
{ 
    UNUSED(param);
   
    return (0);
}

/*---------------------------------------------------------------------------*/
static int StopFunc(void *param)
{
    assert (param);
    
    SchStop(param);
    
    return (1);
}


