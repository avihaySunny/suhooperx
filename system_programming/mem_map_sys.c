#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int global = 0; 

void *ThreadFunctionUno(void *arg); 

int main (void)
{
    static int p = 10; 
    size_t i = 0; 
    pthread_t mythread[3] = {0}; 
    void *myheap = malloc(1000); 
    for (i = 0; i < 3; ++i)
    {
        pthread_create(&mythread[i], NULL, ThreadFunctionUno, &i); 
    }
    /* for (i = 0; i < 3; ++i)
    {
       pthread_join(mythread[i], NULL); 
    }  */
    puts ("\nmain:"); 
    printf("i : %p \n", (void*)&i);
    printf("main heap : %p \n", myheap);  
    printf("fucntion address : %p\n", ThreadFunctionUno); 
    printf("static on main : %p\n", (void*)&p);

    return EXIT_SUCCESS;
}

void *ThreadFunctionUno(void *arg)
{             
    char *msg = "hello"; 
    size_t size = 15; 
    void *stam_ptr = malloc(sizeof(void*)); 
    printf("thread # : %ld \n", *(size_t*)arg); 
    printf("text : %p\n", msg);
    printf("global : %p\n", (void*)&global); 
    printf("stack : %p\n", (void*)&size);
    printf("heap : %p\n", stam_ptr); 
    puts("");

    while(1)
    {
        ++size; 
        if(size > 100000)
        {
            pthread_exit(NULL);
        }
    }

    return arg; 
}