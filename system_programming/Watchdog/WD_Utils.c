/*******************************************************************************
* Programmer: Avihay Asraf
* WD_Utils.c
* File: WD_Utils code
* Date: 
*******************************************************************************/
#define _POSIX_SOURCE 
/* #define _POSIX_C_SOURCE 199309L */
#define _DEFAULT_SOURCE 

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <pthread.h>        /* pthread create / run                      */
#include <unistd.h>         /* for threads                               */
#include <sys/types.h>      /*   thread id                               */
#include <sys/wait.h>       /*                                           */
#include <sys/stat.h>       
#include <signal.h>         /* kill, SIGUSR1 SIGUSR2                     */
#include <semaphore.h>      /* sem wait, sem open                        */
#include <fcntl.h>          /* flags for sempahore                       */

#include "WD_Utils.h"       
#include "sched_scheduler.h" 
#include "sched_task.h"
#include "uid.h"

/* error msgs numbers */
#define SCHED_FAIL (2)
#define TASK_FAIL  (3)
#define SIG_FAIL   (4)
#define FORK_FAIL  (5)
#define EXECV_FAIL (6)
#define TASK_NUM (2)
#define ABS(x)  ((x < 0) ? (-x): (x))
/* ---------------------------------------------------------------------------- */
typedef struct 
{
    sch_t *scheduler; 
    const char *wd_path; 
    const char *app_path; 
    size_t interval; 
    size_t threshold; 

} arg_bundle_t ;

/* ------------------------------------------------------------------------------- */
static void LogWriteError(const char *err_msg);
static void *WDComFunc(void *args); 
static int SendSignalAction(void *param);
static int CheckWDPulse(void *param);
static void InitBundle(arg_bundle_t *bundle, const char *app_path, const char *wd_path, size_t interval, size_t threshold, sch_t *scheduler);
static void SigHandlerUpdateCount(int sig); 
/* ------------------------------------------------------------------------------- */
static int flag_to_stop      = 0; 
static pid_t wd_pid          = 0; 
sig_atomic_t last_seen_counter   = 0; 
static size_t thresh_glob    = 0; 
static pthread_t *thread_ptr = NULL; 
sem_t *sch_run_lock = NULL; 
const char *sem_name = "/sched_lock2"; 
sem_t *client_lock = NULL; 
const char *sem_name2 = "/client_lock"; 
/* ---------------------------------------------------------------------------------------- */
int MMI(const char *app_path, const char *wd_path, size_t interval, size_t threshold)
{
   
    const char *arg_path[2] = {NULL};   
    pthread_t wd_comm_thread = {0}; 
    struct sigaction com_signal = {0};
    sch_t *scheduler = NULL;
    arg_bundle_t arg_bundle = {0};   
    
    thresh_glob = threshold; 
    thread_ptr = &wd_comm_thread; 
    
    scheduler = SchCreate();
    if(NULL == scheduler)
    {   
        LogWriteError("SCHED FAIL");
        return SCHED_FAIL; 
    }
    if(SEM_FAILED == (client_lock = sem_open(sem_name2, O_CREAT, 0666, 0)))
    {
        puts("sem failed");
        return 1; 
    }
    if(SEM_FAILED == (sch_run_lock = sem_open(sem_name, O_CREAT, 0666, 0)))
    {
        puts("sem failed");
        return 1; 
    }
    if(UIDIsBad(SchAdd(scheduler, SendSignalAction, NULL ,interval)))
    {
        LogWriteError("TASK_FAIL");
        SchDestroy(scheduler); 
        return TASK_FAIL; 
    }

    if(UIDIsBad(SchAdd(scheduler, CheckWDPulse, NULL ,interval)))
    {
        LogWriteError("TASK_FAIL");
        SchDestroy(scheduler);
        return TASK_FAIL; 
    }

    com_signal.sa_handler = SigHandlerUpdateCount; 
    com_signal.sa_flags = 0; 
    if (-1 == sigaction(SIGUSR1, &com_signal, NULL))
    {
        LogWriteError("sigaction fail");
        SchDestroy(scheduler);
        return SIG_FAIL; 
    }
    
    InitBundle(&arg_bundle ,app_path, wd_path, interval, threshold, scheduler); 
    
    wd_pid = fork();
    if (0 > wd_pid)
    {   
        LogWriteError("Fork Failed");
        SchDestroy(scheduler);
        return FORK_FAIL; 
    }
    else if (wd_pid == 0)
    {
        arg_path[0] = app_path; 
        if (-1 == execv(wd_path, (char* const*)arg_path))
        {
            LogWriteError("wd execev Failed");
            SchDestroy(scheduler);
            return EXECV_FAIL;
        } 
    }
    else
    {
        pthread_create(&wd_comm_thread, NULL, WDComFunc, &arg_bundle);     
    }
    
    sem_post(client_lock);
    sem_post(client_lock);
    sem_wait(sch_run_lock);
    sem_wait(sch_run_lock);

    return 0; 
}
/* ---------------------------------------------------------------- */
void DNR(void)
{
    void *status = 0; 
    kill(wd_pid, SIGUSR2);
    flag_to_stop = 1; 
    pthread_join(*thread_ptr, &status);
    sem_unlink(sem_name);
}
/* --------------------------------------------------------------------- */
    /* sends signal SIGUSR1 to wd_thread */ 
    /* SCHEDULER TASK 1 */
static int SendSignalAction(void *param)
{
    puts("Client SENT SIGUSR1");
    kill(wd_pid, SIGUSR1); 
    if (flag_to_stop) 
    {
        return 2; 
    }    
    
    (void)param;
    return 0; 
}
/* ----------------------------------------------------------------------- */
            /* SCHEDULER TASK 2 */
static int CheckWDPulse(void *param)
{ 
    char *argv[] = {0, NULL}; 
    if (last_seen_counter + 1 > (int)thresh_glob)
    {
        puts("watchdog died");
        wd_pid = fork(); 
        if (wd_pid == 0)
        {
            execv("./WDEXE", (char * const*) argv);
        } 
        return 1; 
    }
    else 
    {
        ++last_seen_counter;  
    }
    
    (void)param; 
    return 0; 
}
/* ------------------------------------------------------------------------------- */
static void LogWriteError(const char *err_msg)
{
    FILE *fp = fopen("wd_util_log.txt", "a"); 
    if (NULL == fp)
    {
        return; 
    }

    fputs(err_msg, fp);
    fclose(fp);
}
/* ---------------------------------------------------------------------------------- */
static void *WDComFunc(void *args)
{
    arg_bundle_t *bundle = args; 
    assert(args);
    sem_wait(client_lock); 
    sem_post(sch_run_lock);
    SchRun(bundle->scheduler); 
    SchDestroy(bundle->scheduler); 
    
    return args;  
}
/* ---------------------------------------------------------------------------------- */
static void InitBundle(arg_bundle_t *bundle, const char *app_path, const char *wd_path, size_t interval, size_t threshold, sch_t *scheduler)
{
    bundle->app_path = app_path; 
    bundle->wd_path  = wd_path; 
    bundle->interval = interval; 
    bundle->threshold = threshold;
    bundle->scheduler = scheduler; 
}
/* ----------------------------------------------------------------------------------- */
static void SigHandlerUpdateCount(int sig)
{
    puts("CLIENT RECIEVED SIGUSR1");
    last_seen_counter = 0; 
    (void)sig; 
}
/* ----------------------------------------------------------------------------------- */