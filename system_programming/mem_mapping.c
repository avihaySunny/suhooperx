#include <stdio.h>
#include <stdlib.h>

int foobar (void);
int x = 5; 

int main (void)
{
    int var; 
    static int bar; 
    static int bar2;    
    float foo; 
    int *hello = (int*)malloc (sizeof(int)); 
    int *hello2 = (int*)malloc (sizeof(int));    
    printf("stack : %p\n", &var);
    printf("stack : %p\n", &foo);
    printf("bss : %s\n",&bar);
    printf("bss : %p\n",&bar);
    printf("function : %p\n", &foobar);
    printf("malloc : %p\n", hello);
     printf("malloc : %p\n", hello2);
    printf("global : %p\n", &x);
     printf("main : %p\n", main);
    return (0);
}

int foobar (void)
{
    printf("hello");
    return 0;
}
