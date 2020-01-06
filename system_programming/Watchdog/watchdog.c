/*******************************************************************************
* Programmer: Avihay Asraf
* watchdog.c
* File: watchdog code
* Date: 
*******************************************************************************/

#define _POSIX_SOURCE 
#define _DEFAULT_SOURCE 

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <pthread.h>       /* pthread create / run                      */
#include <unistd.h>         /* for threads                               */
#include <sys/types.h>      /*   thread id                               */
#include <sys/stat.h>  
#include <sys/wait.h>       /*                                           */
#include <signal.h>         /* kill, SIGUSR1 SIGUSR2                     */
#include <semaphore.h>      /* sem wait, sem open                        */
#include <fcntl.h>          /* flags for sempahore                       */
#include "watchdog.h"

#include "sched_scheduler.h" 
#include "sched_task.h"

#define INTERVAL (1)
#define THRESH (4)
/* -------------------------------------------------------------------------------- */
sig_atomic_t last_seen_counter   = 0; 
int stop_watchdog = 0; 
static void SigHandlerUpdateCount(int sig);
static int CheckPulse(void *param);
static void SigHandKillWatch(int sig);
static int SendSignalAction(void *param);
static void LogWriteError(const char *err_msg);
/* ------------------------------------------------------------------------------- */
int main (int argc, const char *argv[])
{
    sem_t *sch_run_lock = NULL; 
    const char *sem_name = "/sched_lock2";  
    sem_t *client_lock = NULL; 
    const char *sem_name2 = "/client_lock"; 
    struct sigaction sa = {0};
    struct sigaction sa_usr2 = {0}; 
    pid_t parent_pid = getppid(); 
    sch_t *scheduler = NULL;
    scheduler = SchCreate(); 
    
    if (NULL == scheduler)
    {
        LogWriteError("SCHED CREATE FAILED"); 

        return EXIT_FAILURE;  
    }
    client_lock = sem_open(sem_name2, O_CREAT, 0666, 0); 
    if(SEM_FAILED == (sch_run_lock = sem_open(sem_name, O_CREAT, 0666, 0)))
    {
        return EXIT_SUCCESS;
    }

    sa.sa_handler = SigHandlerUpdateCount; 
    sa.sa_flags = 0; 
    sa_usr2.sa_handler = SigHandKillWatch; 
    sa_usr2.sa_flags = 0; 
    if (-1 == sigaction(SIGUSR1, &sa, NULL))
    {
        return EXIT_FAILURE; 
    }
    if (-1 == sigaction(SIGUSR2, &sa_usr2, NULL))
    {
        return EXIT_FAILURE; 
    }
    if (UIDIsBad(SchAdd(scheduler, SendSignalAction, &parent_pid, INTERVAL)))
    {
        return EXIT_FAILURE; 
    }
    if (UIDIsBad(SchAdd(scheduler,CheckPulse, &argv[0], INTERVAL)))
    {
        return EXIT_FAILURE; 
    }
    sem_wait(client_lock);
    sem_post(sch_run_lock);

    SchRun(scheduler);
    SchDestroy(scheduler);
    sem_unlink(sem_name);
    (void)argc; 
    return EXIT_SUCCESS; 
}
/* ---------------------------------------------------------------------------------- */
static void SigHandlerUpdateCount(int sig)
{
    puts ("-Watch Dog recieved SIGUSR1-");
    last_seen_counter = 0; 
    (void)sig;  
}
/* ----------------------------------------------------------------------------------- */
static void LogWriteError(const char *err_msg)
{
    FILE *fp = fopen("wd_app_log.txt", "a"); 
    if (NULL == fp)
    {
        return; 
    }

    fputs(__TIME__, fp);
    fputs(err_msg, fp);
    fclose(fp);
}
/* ---------------------------------------------------------------------------------------- */
/* task action for scheduler */
static int SendSignalAction(void *pid)
{
    pid_t *parent_id = pid;  
    puts("WatchDog Sent SIGUSR1");
    kill(*parent_id, SIGUSR1);  
    
    return 0; 
}
/* -------------------------------------------------------------------------------------------- */
static int CheckPulse(void *app_path)
{  
    const char *argv[2] = {NULL, NULL}; 
    argv[0] = app_path;
    if (last_seen_counter + 1 > THRESH)
    {   
        puts("Usr App is DEAD");
        if (!stop_watchdog)
        {
            execv("./a.out", (char *const*)argv);  
        }
        
        return 2; 
    }
    else 
    { 
        ++last_seen_counter;  
    }
    
    return 0; 
}
/* --------------------------------------------------------------------------------------------------- */
static void SigHandKillWatch(int sig)
{
    stop_watchdog = 1; 
    (void)sig;  
}
/* ---------------------------------------------------------------------------------------------------- */