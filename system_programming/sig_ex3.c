#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> 

/* THIS IS THE PONG */
pid_t ping_pid = 0; 
void sig_handler(int sig);
static void write_to_log(const char *err_msg);

int main (int argc, char *argv[])
{
    struct sigaction sa = {0};
    if (NULL != argv[1])
    {
        ping_pid = atoi(argv[1]); 
    }

    sa.sa_handler = sig_handler; 
    sa.sa_flags = 0; 
    if (-1 == sigaction(SIGUSR2, &sa, NULL))
    {
        perror("FAIL"); 
        exit(1); 
    }

    kill(ping_pid, SIGUSR1);  

    while(1); 

    (void)argc; 
    return EXIT_SUCCESS; 
}

void sig_handler(int sig)
{
    if (sig == SIGUSR2)
    {
        sleep(1);
        write(0, "Pong\n", 5);
        kill(ping_pid, SIGUSR1); 
    }
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