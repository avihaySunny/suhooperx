/*******************************************************************************
* Programmer: Avihay Asraf
* sched_task.c
* File: sched_task code
* Date: 23/5/19
*******************************************************************************/
#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* malloc                                   */
#include <time.h>           /*time                                      */

#include "sched_task.h"
#include "uid.h"
/*----------------------------------------------------------------------------*/

struct task
{
    uid_type task_id;
    size_t interval; 
    int(*action)(void*);
    void *param;
  	time_t abs_time_to_run;  /* According to absolute clock */
}; 

/*----------------------------------------------------------------------------*/

task_t *SchTaskCreate(size_t interval,  int(*action)(void *param), void* param) 
{
    task_t *task = NULL; 
    
    assert (action);
    
    task = (task_t*)malloc(sizeof(task_t)); 
    if (NULL == task)
    {
        return NULL; 
    }
    
    task->task_id = UIDCreate(); 
    task->interval = interval;
    task->action = action; 
    task->param = param;
    task->abs_time_to_run = time(NULL) + interval;  
    
    return (task); 
}

/*----------------------------------------------------------------------------*/

void SchTaskDestroy(task_t *task)
{   
    if (NULL == task)
    {   
        return;     
    }
    
    task->action = NULL; 
    task->param = NULL;
    free(task); 
    task = NULL; 
}

/*----------------------------------------------------------------------------*/

int SchIsSameTask(const task_t *task, const uid_type *id) 
{   
    assert(task);
    assert(id);
    
    return (id->counter == task->task_id.counter);   
}

/*----------------------------------------------------------------------------*/

time_t SchTaskGetTimeToRun(const task_t *task)
{
    assert(task);
    
    return(task->abs_time_to_run);
}

/*----------------------------------------------------------------------------*/

uid_type SchTaskGetUID(const task_t *task)
{
    assert(task); 
    
    return (task->task_id);
}

/*----------------------------------------------------------------------------*/

int SchTaskGetInterval(const task_t *task)
{
    assert(task);
    
    return (task->interval);
}

/*----------------------------------------------------------------------------*/

void SchTaskSetTimeToRun(task_t *task)
{
    assert(task);
    
    task -> abs_time_to_run = time (NULL) + task->interval; 
}

/*----------------------------------------------------------------------------*/

int SchTaskRunTask(const task_t *task)
{
    assert(task); 
    
    return (task-> action(task->param));
}

