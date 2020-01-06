/****************************************************************************/
/*                               WS9_conversion.c                           */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/
#include <stdio.h>          /*fputs printf          */   
#include <assert.h>         /*  assert              */  
#include <stdlib.h>         /*EXIT_SUCCESS/FAIL     */  
#include <string.h>         /*strlen                */  

#define ASCII_TO(c) (c - '0') 
#define INT_TO(a)   (a + '0')  

static long Atoi(const char *str, int base);    /*  Takes a string returns a long represention          */
static char *Itoa(long number, int base);       /*  Takes and integer returns a string represention copy*/
static void TestItoa(void);                     /*  Tests for Atoi                                      */
static void TestAtoi(void);                     /*  Tests for  Itoa                                     */                             
/****************************************************************************/
int main (void)
{
    puts("Test from integer to string");
    TestItoa();
    puts("\n");
    puts("Test string to int");
    TestAtoi(); 
    puts("\n");
    return (EXIT_SUCCESS);
}

/************TEST FUNCTION **********************************************/ 
static void TestItoa(void)
{
    int base   = 20; 
    long zero  = 0;
    long plus  = 150; 
    long minus = -150; 
     
    char *str_zero  = Itoa(zero, base);
    char *str_plus  = Itoa(plus, base);
    char *str_minus = Itoa(minus , base); 
    
    printf("zero is %ld\n", zero); 
    printf("plus is %ld\n", plus);
    printf("minus is %ld\n", minus);
    
    puts("string represention is:"); 
    printf("zero: %s\nplus: %s\nminus is: %s", str_zero, str_plus, str_minus); 
    
    free(str_plus);
    free(str_minus);    
}

static void TestAtoi(void)
{
    int base        = 16; 
    long zero       = 0; 
    long plus       = 0; 
    long minus      = 0; 
    char *str_zero  = "0";
    char *str_plus  = "150"; 
    char *str_minus = "-150"; 

    zero  = Atoi(str_zero, base);
    plus  = Atoi(str_plus, base);
    minus = Atoi(str_minus, base);
    puts("number represention is:"); 
    printf("zero: %ld\nplus: %ld\nminus is: %ld", zero, plus, minus);       
}

static char *Itoa(long number, int base) 
{
    int dig_count    = 0; 
    int minus        = 0;  
    long num_copy    = 0; 
    char *str_head   = NULL;
    char *str_runner = NULL; 
    char *str_end    = "0";  /* in case number is zero */
    char digit       = 0; 
      
    if (0 == number)
    {
        return (str_end);
    }
    
    if (number < 0)
    {
        number *= -1;  
        minus = 1;   
    }
    
    num_copy = number; 
    while (0 != num_copy)
    {
        ++dig_count;
        num_copy /= base;  
    }
    
    str_head = (char*)malloc(sizeof(char) * (dig_count + minus + 1));
    if (str_head == NULL)
    {
        fputs("MEM ERROR", stderr);
        return NULL; 
    }
    
    if (minus) /*if it's a negetive number*/
    {
        *str_head = '-';  
    }
    
    str_runner  = str_head + dig_count + minus;   
    *str_runner = '\0';
    --str_runner; 
    num_copy = number; 
    while(0 != num_copy) 
    {
        digit = (num_copy % base); 
        if ((10 <= digit) && (base >= digit))
        {
            digit += 'A' - 10;  
        }
        else
        {
            digit = INT_TO(digit);
        }
        
        *str_runner = digit; 
        num_copy /= base; 
        --str_runner; 
    } 
    return (str_head);   
}

static long Atoi(const char *str, int base)
{
    long number            = 0; 
    long minus             = 0; 
    size_t i               = 0;
    size_t dig_count       = 0;  
    const char *str_runner = str;
    char digit             = 0; 
    
    assert(str); 
    while(' ' == *str)
    {
        ++str; 
    }
    
    if ('-' == *str)
    {
        minus = -1;             
    }
    
    dig_count = strlen(str) + minus;
    str_runner = str - minus; 
    for (i = 0; i < dig_count ; ++i, ++str_runner)
    { 
        digit = *str_runner;
        if (('A' <= digit) && (digit <= 'Z'))
        {
            digit -= 'A' + 10;    
        }
        else 
        {
            digit = ASCII_TO(digit);    
        } 
        
        number = (number * base) + digit;  
    }
    
    return ((minus) ? (-number) : (number)); 
}
