 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <sys/wait.h>

 int main (int argc, char *argv[])
 {
    pid_t pid = 0; 
    int status = 0; 
    while (pid != -1)
    {
        if ((pid = fork()) == -1)
        {
            puts("fork fail");
            break;
        }
        else if (pid == 0)
        {
            execv(argv[1], argv);
        }

        pid = wait(&status);
    }
    
    (void)argc;
    return EXIT_SUCCESS;
 }
