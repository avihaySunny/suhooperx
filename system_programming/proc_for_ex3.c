#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> 

static void sig_action(int sig,siginfo_t *siginfo, void *context);
static void write_to_log(const char *err_msg);

/* THIS IS THE PING  */
int main ()
{  
    struct sigaction sa = {0}; 
    sa.sa_flags |= SA_SIGINFO;  
    sa.sa_sigaction = sig_action; 
    
    if(-1 == sigaction(SIGUSR1, &sa, NULL))
    {
        write_to_log("sigaction fail");
        exit(1); 
    }
    while (1)
    {
        /* DO NOTHING SORRYYYYY */
    }   
}

static void sig_action(int sig,siginfo_t *siginfo, void *context)
{
    pid_t sender_pid = siginfo->si_pid; 
    sleep(1); 
    write(0, "Ping\n", 5); 
    kill(sender_pid, SIGUSR2);
    (void)sig; 
    (void)context; 
}

static void write_to_log(const char *err_msg)
{
    FILE *fp = fopen("log.txt","a");
    if (NULL == fp)
    {
        return; 
    }
    fputs(err_msg, fp);
    fclose(fp);
}