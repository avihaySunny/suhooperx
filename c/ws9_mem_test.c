/****************************************************************************/
/*                                      WS9_mem_test.c                      */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/
#include <stdio.h>                  /*printf, puts      */
#include <stdlib.h>                 /*EXIT SUCCESS/FAIL */

#include "ws9_mem.h"

static void TestMemset(void);         /* Tests Memset                      */ 
static void TestMemcpy(void);         /* Tests Memcpy                      */
static void TestMemmove(void);        /* Tests Memmove                     */ 
/**************************MAIN*********************************************/
int main (void)
{    
   puts("Test Memset"); 
   TestMemset();
   puts("Test Memcpy");
   TestMemcpy();
   puts("Test Memmove");  
   TestMemmove(); 
   
    #if 0 
    char test[8] = {0}; 
    Memcpy(test,"1234567",8);
    printf("%s", test);*/
   #endif
   return 0;
}
/*****************TEST**FUNCTIONS*******************************************/
static void TestMemset(void)
{
    int i = 0; 
    char *c_ptr = (char*)malloc (517);
    char *c = c_ptr;
    
    if (NULL == c_ptr)
    {
        fputs("MEM FAIL",stderr); 
        return;  
    }
    
    if (!((size_t)c_ptr % 8))         /*creates an undivisible by 8 address*/
    {
        c_ptr += 3;  
    }
   
    Memset(c_ptr,'A', 152); 
    for (i = 0; i < 150; ++i, ++c_ptr)
    {
        printf(" i = %d %c\n", i, *c_ptr); 
    }
    
    free(c);
}   

static void TestMemcpy(void)
{
    int i = 0; 
    char *c_ptr = (char*)malloc (517);
    char *copied = (char*)malloc(517);
    char *c = c_ptr, *sec_c = copied; 
    
    if ((NULL == c_ptr) || (NULL == copied))
    {
        fputs("MEM FAIL",stderr); 
        return;  
    }
    
    if (!((size_t)c_ptr % 8))     /*creates an unaligned address*/
    {
        c_ptr += 3;  
    }
    
    Memset(sec_c,'A',152); 
    Memcpy(c_ptr, sec_c, 152);
    for (i = 0; i < 150; ++i, ++c_ptr)
    {
        printf(" i = %d %c\n", i, *c_ptr); 
    }
    
    free(c);
    free(sec_c);
}  

static void TestMemmove(void)
{
    int i = 0; 
    static char arr[150] = {0}; 
    static char arr1[150] = {0};

    Memset(arr,'A', 150);
    Memmove(arr1, arr, 150);
    for (i = 0; i < 150; ++i)
    {
        printf(" i = %d %c\n", i, arr1[i]); 
    }  
}
