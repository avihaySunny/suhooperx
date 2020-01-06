/*******************************************************************************
* Programmer: Avihay Asraf
* recursion_test.c
* File: recursion testing
* Date: ה' יונ 13 14:55:04 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include <sys/time.h>         /*timeval */
#include "recursion.h"

#define SUCCESS (0)
#define FAIL (1)

static float RealTimeDiff(struct timeval *a, struct timeval *b);
static void TestFibTime(void);
static int TestStrlen(void);
static int TestStrcmp(void);
static int TestStrcat(void);
static int TestStrcpy(void);
static int TestStrstr(void);

int main(void)
{   
     TestFibTime();  
    if (FAIL == TestStrlen())
    {
        puts ("STRLEN TEST FAIL");
    }

    if (FAIL == TestStrcmp())
    {
        puts ("Strcmp TEST FAIL");
    }

    if (FAIL == TestStrcat())
    {
        puts ("Strcat TEST FAIL");
    }

    if (FAIL == TestStrcpy())
    {
        puts ("Strcpy TEST FAIL");
    }

      if (FAIL == TestStrstr())
    {
        puts ("Strstr TEST FAIL");
    }

    return (EXIT_SUCCESS);
}

static void TestFibTime(void)
{
    struct timeval start = {0};
    struct timeval end = {0}; 

    gettimeofday(&start, NULL);
    Fibonacci(10); 
    gettimeofday(&end, NULL);
    printf("Iterative time : %1.4f\n", RealTimeDiff(&start, &end));
    
    gettimeofday(&start, NULL);
    Fib(44);
    gettimeofday(&end, NULL);
    printf("Recursive time : %1.4f\n", RealTimeDiff(&start, &end));

}

static float RealTimeDiff(struct timeval *a, struct timeval *b) /*returns seconds*/
{
    assert(a && b);
    return (((b->tv_sec*1e6 + b->tv_usec) - (a->tv_sec *1e6 + a->tv_usec)) / 1000000);
}

static int TestStrlen(void)
{
    char *a = "aaaaaaaaaaaaaa";
    char *empty = "";

    if (strlen(a) != Strlen(a) && strlen(empty) != Strlen(empty))
    {
        return FAIL; 
    }
        
    return SUCCESS; 
}

static int TestStrcmp(void)
{
    char *a = "XXXXXX";
    char *b = "XXXXXX"; 
    char *c = "XXX";
    int fails = 0; 

    (strcmp(a,b) == Strcmp(a,b) ? (0): (++fails));
    (strcmp(a,c) == Strcmp(a,c) ? (0): (++fails));

    return !(fails == 0);
}

static int TestStrcat(void)
{
    char a[15] = "SLSL"; 
    char b[15] = "SLSL"; 
    char *c = "XXX";
    char *d = "";
    int fails = 0;

    Strcat(a, c); 
    strcat(b, c);

    !strcmp(a,b) ? (0) : (++fails);

    Strcat(a, d); 
    strcat(b, d);

    !strcmp(a,b) ? (0) : (++fails);
    
    return !(fails == 0);
}

static int TestStrcpy(void)
{
    char a[15] = "SLSL"; 
    char b[15] = "DDDD"; 
    char *c = "";
    int fails = 0;

    Strcpy(a, b); 
 
    !strcmp(a,b) ? (0) : (++fails);

    strcpy(a, c);

    !strcmp(a,c) ? (0) : (++fails);
    
    return !(fails == 0);
}

static int TestStrstr(void)
{
    char needle[] = "sixtyseven"; 
    char haystack[] = "fourthousandsixtyseveneight"; 
    char noneedle[] = "toshibahere"; 
    int fails = 0; 
    if (strstr(haystack, needle) != Strstr(haystack, needle))
    {
        ++fails;
    }

    if (strstr(haystack, noneedle) != Strstr(haystack, noneedle))
    {
        ++fails;
    }

    return !(fails == 0);
}