/*******************************************************************************
* Programmer: Avihay
* sched_scheduler.h
* File: sched_scheduler header
* Date: ה' מאי 23 13:48:36 IDT 2019
*******************************************************************************/

#ifndef __SCHED_SCHEDULER_H__
#define __SCHED_SCHEDULER_H__

#include "uid.h"

typedef struct scheduler sch_t;

/* Creates new scheduler.
   Returns an address on success, NULL on failure */
sch_t *SchCreate(void);


void SchDestroy(sch_t *sch); 

/* Creates new task and adds it to schedule.
   Action func returns:
   0 = success and again
   1 = success and not again
   2 = fail and not again 
   Returns uid on success and bad uid on failure
   Action func must be valid */
uid_type SchAdd(sch_t *sch, int(*action)(void *param), void *param, size_t interval); 

/* Returns int(status), 0 = SUCCESS, 1 = FAILURE */    
int SchRemove(sch_t *sch, uid_type id);  

/* Starts running scheduler. */
void SchRun(sch_t *sch); 

/* Stops scheduler.
   Maintains queue till next run */
void SchStop(sch_t *sch); 

/* Returns int(bool), 1 = empty, 0 = not empty */ 
int SchIsEmpty(const sch_t *sch); 

/* Returns number of tasks in scheduler */ 
size_t SchSize(const sch_t *sch); 

#endif          /* sched_scheduler  */







