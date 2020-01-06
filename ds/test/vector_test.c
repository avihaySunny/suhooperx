#include <assert.h> 	    /* assert                                         */
#include <stdio.h> 		    /* printf                                         */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc       */
#include <string.h>         /* strcat, strlen, strcpy                         */

#include "vector.h"
/*****************************************************************************/
static void TestVecCreate(void);
static void TestVecPush(void);
static void TestVecGetAddress(void);
static void TestVecGrowth(void);
static void TestVecShrink(void); 
static void TestEmptyPop(void);
DBG(static void TestVecPrint(void);)
DBG(static void VecPrintInt(void *to_print);) /* for PrintVecTest*/  

/****************MAIN*********************************************************/
int main(void)
{ 
    puts(YELLOW"Vector create Test:"RESET);
    TestVecCreate();
    
    puts(YELLOW"Vector push Test"RESET);
    TestVecPush();
    
     puts(YELLOW"Vector read Test"RESET);
    TestVecGetAddress();
    
    puts(YELLOW"Vector growth Test"RESET);
    TestVecGrowth();   
    
    puts(YELLOW"Vector shrink Test"RESET);
    TestVecShrink(); 

    puts(YELLOW"Vector empty pop Test"RESET);
    TestEmptyPop();
    
    DBG(puts(RED"DEBUG MODE:");)
    DBG(puts(YELLOW"Vector print Test"RESET)); 
    DBG(TestVecPrint());
    
    return (EXIT_SUCCESS);
}

static void TestVecCreate(void)
{
    vect_t*vec = VecCreate(sizeof(int), 100);
    VecDestroy(vec);
    (NULL == vec) ? puts (RED"Fail"RESET) : puts(CYAN"SUCCESS"RESET);

}

static void TestVecPush(void)
{
    ssize_t err = 1, i = 0; 
    
    vect_t*vec = VecCreate(sizeof(int), 10);
    if (NULL == vec)
    {
        puts(RED"FAIL");
        return;       
    }
    
    for (i = 0; i < 18 && -1 != err ; ++i)
    {
        err = VecPush(vec, &i);
    }
    
    (20 == VecGetCapacity(vec)) ? puts(CYAN"SUCCESS") : puts(RED"FAIL"); 
    VecDestroy(vec); 
}

static void TestVecGetAddress(void)
{
    ssize_t i = 0, err = 1; 
    
    vect_t*vec = VecCreate(sizeof(int), 10);  
    if (NULL == vec)
    {
        puts(RED"FAIL");
        return;       
    }
   
    for (i = 0; i < 18 && -1 != err ; ++i)
    {
        err = VecPush(vec, &i);
    }
    
    if(-1 == err)
    {
        puts(RED"FAIL");
        return;    
    }
    
    for(i = 0; i < 18; ++i)
    {
       if(i != *(int*)VecGetItemAddress(vec, i))
       {
            puts(RED"FAIL");
            return; 
       }
    }  
     
    VecDestroy(vec); 
    puts(CYAN"SUCCESS");     
}

static void TestVecGrowth(void)
{
    ssize_t vec_size = 10;
    ssize_t i = 0;
    ssize_t success_count = 0;
    ssize_t err = 0;
    
    vect_t*vec = VecCreate(sizeof(int), vec_size);  
    if (NULL == vec)
    {
        puts(RED"Vector Creation FAIL");
        
        return;       
    }
    
    for (i = 0; i < 10 * vec_size; ++i)
    {
        err = VecPush(vec, &i); 
        if((i == 15) && (20 == VecGetCapacity(vec))) 
        {
           ++success_count; 
        }
        
        if((i == 35) && (40 == VecGetCapacity(vec)))
        {
           ++success_count; 
        }
        
        if((i == 75) && (80 == VecGetCapacity(vec)))
        {
           ++success_count; 
        }
        
        if((i == 99) && (160 == VecGetCapacity(vec)))
        {
           ++success_count; 
        } 
    } 
    
    if ((4 == success_count) && (err != -1))
    {
        VecDestroy(vec);
        puts(CYAN"SUCCESS"); 
        return; 
    }
    if(err == -1)
    {
        puts(RED"Growth Resize FAIL-push");
    }
    if(4 != success_count)
    {
        puts(RED"Growth Resize FAIL-capacity test"RESET);
    }
    
    VecDestroy(vec);
    
}

static void TestVecShrink(void)
{
    ssize_t vec_size = 200;
    ssize_t i = 0;
    ssize_t err = 0;
    
    vect_t*vec = VecCreate(sizeof(int), vec_size);  
    if (NULL == vec)
    {
        puts(RED"Vector Creation FAIL");
        return;       
    }
     
    for (i = 0; i < 10 ; ++i)     /*push some elements so resize will work */
    {
        err = VecPush(vec, &i);
        if (-1 == err)
        {
            puts(RED"push FAIL");
            return;      
        } 
    }
    
    for (i = 0; i < 10; ++i)
    {
        err = VecPop(vec); 
    } 
    
    if(err == -1)
    {
        puts(RED"Growth Resize FAIL-push");
        return;
    }
    
    if(3 != VecGetCapacity(vec))
    {
        puts(RED"Growth Resize FAIL-capacity test"RESET);
        return;
    }
    
    puts(CYAN"SUCCESS"); 
    VecDestroy(vec);
}

static void TestEmptyPop(void)
{
    ssize_t vec_size = 200;
    ssize_t i = 0;
    ssize_t success_count = 0;
    ssize_t err = 0;
    
    vect_t*vec = VecCreate(sizeof(int), vec_size); 
    if (NULL == vec)
    {
        puts(RED"Vector Creation FAIL");
        return;       
    }
    
    for (i = 0; i < 10; ++i)
    {
        err = VecPop(vec); 
        if(-1 == err)
        {
            ++success_count;
        }
    } 
    
   (success_count == 10) ? puts(CYAN"SUCCESS") : puts(RED"FAIL"); 
   VecDestroy(vec);
}

#ifndef NDEBUG 
static void TestVecPrint(void)
{
  ssize_t vec_size = 200;
  ssize_t err = 0;
  ssize_t i = 0;
  
  vect_t*vec = VecCreate(sizeof(int), vec_size);
  if (NULL == vec)
    {
        puts(RED"Vector Creation FAIL");
        return;       
    }
    
  puts(GREEN"EMPTY VEC Print Test:"RESET);
  VecPrint(vec, NULL, 0); 
  
  for (i = 0; i < 10 ; ++i)         /*push some elements so resize will work */
    {
        err = VecPush(vec, &i);
        if (-1 == err)
        {
            puts(RED"push FAIL");
            return;      
        } 
    }
  
  puts(WHITE"Printing vec data:"RESET);
  VecPrint(vec, VecPrintInt, 10); 
 
  puts(WHITE"Printing with data and null pointer:"RESET);
  VecPrint(vec, NULL, 0);
  VecDestroy(vec);
}
#endif
 
void VecPrintInt(void *to_print)
{
    assert(to_print);
    printf("%d\n",*(int*)to_print);
}

