 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <sys/types.h>
 #include <string.h>
 #include <sys/wait.h>

 static void RunSimpleShell(char *argv[]); 
 static char *FindArgPtr(char *expression);

 int main (int argc, char *argv[])
 {
    RunSimpleShell(argv);
     
    (void)argc;

    return EXIT_SUCCESS;
 }

 static void RunSimpleShell(char *argv[])
 {
    char command_buff[500] = {0}; 
    char original_address[] = "/bin/";
    char full_cmd_buff[600] = {0};
    char *arg_ptr = NULL;
    char *myargv[3] = {NULL, NULL, NULL};
    int status = 0; 
    pid_t pid = 0; 
    myargv[0] = argv[0];
    
    while (strncmp("-exit\n", command_buff, 5)) 
    {
        fgets(command_buff, 500, stdin);
        arg_ptr = FindArgPtr(command_buff);
        *(arg_ptr + strlen(arg_ptr) - 1) = '\0'; 
        strcpy(full_cmd_buff, original_address); 
        strncat(full_cmd_buff, command_buff, strlen(command_buff));

        myargv[1] = arg_ptr;

        if ((pid = fork()) == -1)
        {
            break;  
        }
        else if (pid == 0) 
        {
            execv(full_cmd_buff, myargv);   
        }  
    
        pid = wait(&status);
        memset(full_cmd_buff, 0, 600);  
    }
 }

 static void *SetArgPtr(char *expression, char **myargv)
 {
    size_t i = 0; 

    while (expression != '\0')
    {  
        if (*expression == ' ')
        {
            ++i; 
        }
        ++expression;
    }
     
        *expression = '\0';

    }
 }