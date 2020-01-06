/*******************************************************************************
* Programmer: Avihay
* sched_task.h
* File: sched_task header
* Date: ה' מאי 23 13:47:46 IDT 2019
*******************************************************************************/

#ifndef __SCHED_TASK_H__
#define __SCHED_TASK_H__

#include "uid.h"

typedef struct task task_t;

/* Creates task.
   Returns NULL on failure, or task address on success. */
task_t *SchTaskCreate(size_t interval,  int(*action)(void *param), void* param);

/* Allowes NULL as argument */
void SchTaskDestroy(task_t *task);

/* Returns int(status)
   0 = success and again
   1 = success and not again
   2 = fail and not again    */
int  SchTaskRunTask(const task_t *task);

/* Returns 1 if same task = TRUE 
   task = existing uid, id = uid to find */
int SchIsSameTask(const task_t *task, const uid_type *id);

/* Returns task's interval ?*/
int SchTaskGetInterval(const task_t *task);

/* Returns time till next task run */
time_t SchTaskGetTimeToRun(const task_t *task);

/* Updates time till next run of task */
void SchTaskSetTimeToRun(task_t *task);

/* Gets uid of task */
uid_type SchTaskGetUID(const task_t *task);

void PrintTask(task_t *task);

#endif          /* sched_task  */







