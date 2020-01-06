#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h> 

void sigusr1_handler(int sig);
void sigusr2_handler(int sig);
int sig_count1 = 0;

int main (int argc, char *argv[])
{
    pid_t pid = 0; 
    int count = 0; 
    int status = 0; 
    

    (void) signal(SIGUSR1, sigusr1_handler);
    (void) signal(SIGUSR2, sigusr2_handler);
    
    pid = fork(); 
    if (pid < 0)
    {
        puts("can't create new process\n"); 
    }
    else if (pid != 0)
    {
        while(1)
        {
            raise(SIGUSR2); 
            ++count; 
            wait(&status); 
        }
    }
    else
    {
        while(1)
        {
            execv("appex2", argv);
            ++count;
        }  
    }

    (void)argc;
    return EXIT_SUCCESS;
}

void sigusr1_handler(int sig)
{   
    if(sig_count1 < 500)
    {
        signal(SIGUSR1, sigusr1_handler);
        ++sig_count1; 
        puts ("pong 1");
        raise(SIGUSR2); 
        sleep(2);
    }
    
    (void)sig;
}

void sigusr2_handler(int sig)
{
    if (sig_count1 < 500)
    {
        signal(SIGUSR2, sigusr2_handler);
        ++sig_count1;
        puts ("ping 1");
        raise(SIGUSR1);
        sleep(2);
    }

    (void)sig;
}



