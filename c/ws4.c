/****************************************************************************/
/*                                      WS4.c                               */
/*                                   Avihay Asraf                           */                
/*                                    April 2019                            */
/****************************************************************************/
#include <stdio.h>    /*       printf,puts,getchar           */                                  
#include <stdlib.h>   /* int system + EXIT_FAILURE/SUCCESS   */

#define SIZE (256)      /*  size for func pointer array   */  
#define FAIL (-1)       /* For system func fail           */ 
#define ESC (27)        /*Const val for 'Esc'             */ 

static void AtSwitch(void);      /* perfom using switch case     */
static void AtIf(void);          /* perfom using if/else         */
static void AtLut(void);         /* perfom using look up tables  */
static void PrintA(void);        /* prints case A is pushed      */
static void PrintT(void);        /* prints case T is pushed      */
static void PrintNone(void);     /* Empty func for pointer       */

int main(void)
{
    int ret_val = 0; 
    ret_val = system("stty -icanon -echo"); /* for hiding key strokes */ 
    
    if (FAIL == ret_val)
    {
       return (EXIT_FAILURE);
    }
    
    puts("This is using switch/case: \n");
    AtSwitch();
    
    puts("This is using if/else: \n");
    AtIf();
    
    puts("This is using function pointers: \n");
    AtLut();
    
    ret_val = system("stty icanon echo");
    
    if (FAIL == ret_val)
    {
        return (EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS; 
}

static void AtSwitch(void)
{   
    char c = '0';

    while ((ESC != c) && (-1 != c)) /* /*checks end of input or fail to input */
    {
        c = getchar();
        switch (c)
        {
            case 'A': 
            {
                puts("A Pressed \n");
                break;
            }
            
            case 'T': 
            {
                puts("T Pressed \n");
                break;
            }       
        }
    }
}

static void AtIf(void)
{
    char c = '0';
    
    while ((ESC != c) && (-1 != c)) /*checks end of input or fail to input */
    {
        c = getchar();
        
        if('T' == c)
        {
            puts("T Pressed \n");
        }
        if('A' == c)
        {
            puts("A Pressed \n");
        }       
    }
}

static void PrintA(void)
{
    puts("A was pressed\n");
}

static void PrintT(void)
{
    puts("T was pressed\n");
}

static void PrintNone(void) 
{
    /*empty function*/
}

static void AtLut(void)
{
    int  i = 0; 
    char c = '0'; 
    void (*func_ptr[SIZE])(void);
     
    for(; i < SIZE; ++i)
    {
        func_ptr[i] = PrintNone;
    }
    
    func_ptr['A'] = PrintA; 
    func_ptr['T'] = PrintT;           
    
    while ((ESC != c) && (-1 != c))  /*checks end of input or fail to input */
    {
        c = getchar(); 
        (func_ptr[(int)c])();    
    }          
}
