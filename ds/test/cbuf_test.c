/*******************************************************************************
* Programmer: Avihay Asraf
* cbuf_test.c
* File: cbuf testing
* Date: א' מאי 12 17:47:49 IDT 2019
*******************************************************************************/
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE                */

#include "./include/cbuf.h"

static void TestCBUfCreate(void); 
static void TestCBufWrite(void);
static void TestCBufRead(void);
static void TestCBufPrint(void);
static void IntergrationTest(void);

/**********************MAIN**********************************************/
int main(void)
{
    puts("BufCreate Test:");
    TestCBUfCreate();
    
    puts("BufWrite Test:");
    TestCBufWrite();
    
    puts("BufRead Test:");
    TestCBufRead();
    
    
    puts("BufPrint Test:");    
    DBG(TestCBufPrint();)
    
    puts("Intergration Test:");  
    IntergrationTest();
    
    return (EXIT_SUCCESS);
}

/*******************TEST FUNCTIONS*****************************************/
static void TestCBUfCreate(void)
{ 
     
    cbuf_t *cb = CBufCreate(50 * sizeof(int));
    if (NULL == cb)
    {
        puts(RED"FAIL"RESET);
        return;
    }
    
    puts(GREEN"SUCCESS"RESET);
    CBufDestroy(cb);
    
    return;
}

static void TestCBufWrite(void)
{
  int i = 0, count = 0; 
  cbuf_t *cb = CBufCreate(10 * sizeof(int));
  
  for (i = 0; i < 15; ++i)
    {
        count += CBufWrite(cb, &i, sizeof(int));      
    }
    
    if ((count == 35) && (!CBufGetFreeSpace(cb)))
    {
        puts(GREEN"SUCCESS"RESET);
        CBufDestroy(cb);
        return;
    }
    
    puts(RED"FAIL"RESET);
    CBufDestroy(cb);
    return;
}    

static void TestCBufRead(void)
{
  int i     = 0;
  int count = 0;
  int dest  = 0;  
  cbuf_t *cb = CBufCreate(10 * sizeof(int));
  
    for (i = 0; i < 15; ++i)
    {
        CBufWrite(cb, &i, sizeof(int));      
    }

    for (i = 0; i < 15; ++i)
    {
        count += CBufRead(cb, &dest, sizeof(int));        
        if (i >= 0 && i < 10) 
        {
            if(dest != i)
            {
                puts(RED"aREAD Fail\n");
                CBufDestroy(cb); 
                return;
            }
        }   
    }
   
    if ((count == 35) && (CBufGetFreeSpace(cb) == 40))
    {
        puts(GREEN"SUCCESS\n"RESET);
        CBufDestroy(cb); 
        return;
    }
    
    puts(RED"FAIL READ"RESET);
    CBufDestroy(cb);
    return;
}    
  
#ifndef  DNDEBUG
static void TestCBufPrint(void)
{
    int i = 0;
    int a = 'c';
    cbuf_t *cb = CBufCreate(10 * sizeof(char));

    for (i = 0; i < 10; ++i)
    {
        CBufWrite(cb, &a, sizeof(char));      
    }
    
    CBufPrint(cb, sizeof(int) * 12);
    CBufDestroy(cb);
    return;
}    

#endif /*debug test*/

static void IntergrationTest(void)
{
    int i = 0;
    int a = 'c';
    cbuf_t *cb = CBufCreate(30 * sizeof(char));

    for (i = 0; i < 28; ++i)
    {
        CBufWrite(cb, &a, sizeof(char));      
    }
    
    for (i = 0; i < 5; ++i)
    {
        CBufRead(cb, &a, sizeof(char));
    }
    
    for (i = 0; i < 4; ++i)
    {
        CBufWrite(cb, &a, sizeof(char));      
    }
    
    for (i = 0; i < 15; ++i)
    {
        CBufRead(cb, &a, sizeof(char));
    }
    
    if (17 == CBufGetFreeSpace(cb)) 
    {
         puts(CYAN"SUCCESS");
         CBufDestroy(cb);
         return; 
    }
    
    puts(RED"FAIL READ"RESET);
    CBufDestroy(cb); 
}

