/*******************************************************************************
* Programmer: Avihay Asraf
* sched_scheduler.c
* File: sched_scheduler code
* Date: 23/5/19 
*******************************************************************************/
#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /*   malloc                                 */
#include <time.h>           /* time_t                                   */
#include <unistd.h>         /* sleep                                    */

#include "p_queue.h"
#include "sched_task.h"
#include "sched_scheduler.h"


#define RERUN (0)

static void SchRemoveAll(sch_t *sch);
static int CmpData(const void *dataA, const void *dataB);
static int IsTaskId(const void *task, const void *id);

/*-----------------------------------------------------------------------------*/
struct scheduler
{
    pq_t *tasks; 
    unsigned char is_stop; 
};

/*-----------------------------------------------------------------------------*/

sch_t *SchCreate(void)
{
    sch_t *sch = (sch_t*)malloc(sizeof(sch_t));
    if (NULL == sch)
    {
        return NULL; 
    }
    
    sch->tasks = PQCreate(CmpData);
    if (NULL == sch->tasks)
    {
        free(sch);
        sch = NULL; 
    }
    
    sch->is_stop = 0; 
    
    return (sch); 
} 
/*-----------------------------------------------------------------------------*/

void SchDestroy(sch_t *sch)
{
    if (NULL == sch)
    {
        return;
    }
    
    SchRemoveAll(sch); 
    PQDestroy(sch->tasks);
    sch->tasks = NULL; 
    free(sch); 
    sch = NULL; 
}

/*-----------------------------------------------------------------------------*/

int SchRemove(sch_t *sch, uid_type id)
{
    task_t *task = NULL; 
   
    assert(sch); 
   
    task = PQRemove(sch->tasks, IsTaskId, &id);
    
    if (NULL == task)
    {
        return (1);
    }
    
    SchTaskDestroy(task);
    task = NULL; 
    
    return (0);
}

static int IsTaskId(const void *task, const void *id)
{
    return (SchIsSameTask(task, id));
}

/*-----------------------------------------------------------------------------*/

uid_type SchAdd(sch_t *sch, int(*action)(void *param), 
                                            void *param, size_t interval)
{
    task_t *task = SchTaskCreate(interval, action, param);
   
    assert(param);
    assert(action);
   
    if (NULL == task)
    {
        SchTaskDestroy(task);
        task = NULL; 
        return (UIDGetBadUID());
    }

    PQEnqueue(sch->tasks, task);
    
    return SchTaskGetUID(task);
}
/*-----------------------------------------------------------------------------*/

void SchRun(sch_t *sch)
{
    time_t task_time = 0; 
    task_t *task = NULL; 
    int status = 0;
    
    assert(sch);
         
    sch->is_stop = 0; 
    while ((!PQIsEmpty(sch->tasks)) && (!sch->is_stop))
    {
        task_time = SchTaskGetTimeToRun(PQPeek(sch->tasks)); 
        
        if (time (NULL) >= task_time) 
        {
            task = PQDequeue(sch->tasks);
            status =  SchTaskRunTask(task);  
            if (RERUN == status)
            {   
                SchTaskSetTimeToRun(task);    
                if (0 != PQEnqueue(sch->tasks, task)) 
                {
                    SchTaskDestroy(task);
                } 
            }
            else
            {
                SchTaskDestroy(task);
            }  
        }
        else
        {
            sleep((task_time - time(NULL)) * ((task_time - time(NULL)) > 0));
        }
    }
    
    task = NULL; 
}
/*-----------------------------------------------------------------------------*/

void SchStop(sch_t *sch)
{
    if (NULL == sch->tasks)
    {
        return; 
    }
    sch->is_stop = 1;
}

/*-----------------------------------------------------------------------------*/

int SchIsEmpty(const sch_t *sch)
{
    assert(sch);
    
    return (PQIsEmpty(sch->tasks)); 
}

/*-----------------------------------------------------------------------------*/

size_t SchSize(const sch_t *sch)
{
    assert(sch);
    
    return (PQSize(sch->tasks));
}

static void SchRemoveAll(sch_t *sch)
{
    assert(sch);
    
    while (!SchIsEmpty(sch))
    {
        SchTaskDestroy(PQDequeue(sch->tasks)); 
    }
}
/*-------------------HelperFunction-----------------------------------------*/
static int CmpData(const void *dataA, const void *dataB)
{
    assert(dataA);
    assert(dataB);
    
    return (SchTaskGetTimeToRun(dataA) < SchTaskGetTimeToRun(dataB));      
}
/*---------------------------------------------------------------------------*/

