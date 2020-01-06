/****************************************************************************/
/*                                      WS9_other.c                         */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/
#include <stdio.h>      /*fputs, printf         */
#include <assert.h>     /* assert               */
#include <stdlib.h>     /* EXIT_SUCCESS/FAILURE */
#include <ctype.h>      /* tolower              */

#define ALPHBET (26)  
#define IS_LITTLENDIAN  ((*(unsigned short*)"\1") == 1)    
#define SIZEARR(x) ((sizeof(x)/sizeof(x[0])))          
/****************************************************************************/
static void PrintLetters(char arr1[], char arr2[], char arr3[],
                         int size1,int size2, int size3);  /*Prints letter that exist on arr1 and 2 but not on the 3rd*/                         
static void TestPrintLetters(void);                        /* Test For PrintLetters    */
static int IsLittleEndian(void);                           /* check if little endian   */                            
static void TestEndiannes(void);                           /*FOR ENDIANNES MACRO TEST   */
/********************MAIN*************************************************/

int main (void)
{    
    TestEndiannes();
    TestPrintLetters(); 
    return EXIT_SUCCESS;
}

/*********TEST FUNCTIONS**************************************************/

static void TestPrintLetters(void)
{
     char arr1[] = {'a', 'b','d','e','h'};
     char arr2[] = {'a', 'b','h','d','e'};
     char arr3[] = {'a','e', 'l', 'g','r','k'};
     int size1 = SIZEARR(arr1);
     int size2 = SIZEARR(arr2);
     int size3 = SIZEARR(arr3); 
     PrintLetters(arr1, arr2, arr3, size1, size2, size3);   
}

static void TestEndiannes(void)
{   
    if(IS_LITTLENDIAN)
    printf("Little Endian");
    puts(" ");
    if(IsLittleEndian())
    printf("Little Endian\n");
}
/*****************FUNCTIONS************************************************/

static void PrintLetters(char arr1[], char arr2[], char arr3[],
                         int size1,int size2, int size3)
{
    int histogram[ALPHBET] = {0};  
    int i = 0; 
    
    assert(arr1);
    assert(arr2);
    assert(arr3);
    
    for (i = 0; i < size1; ++i)
    { 
        histogram[tolower(arr1[i]) - 'a'] = 1;    
    }
 
    for (i = 0; i < size2; ++i)
    {
        if (1 == histogram[tolower(arr2[i]) - 'a'])
        {
            histogram[tolower(arr2[i]) - 'a'] = 'Y';  /* just to distinguish */ 
        }
    }
    
    for (i = 0; i < size3; ++i)
    {
        histogram[tolower(arr3[i]) - 'a'] = 0;
    }
    
    puts ("Common later array 1 & 2 ! 3 are :");
    for (i = 0; i < ALPHBET; ++i)
    {
        if ('Y' == histogram[i])
        {   
            printf("%c", i + 'a');
        }  
    }
    puts(" ");
}

static int IsLittleEndian(void)
{
    int i = 1; 
    char *p = (char*)&i; 
    return (*p);
}

#if 0
static int IsLittleEndian(void)
{
    size_t num        = 0x86451716; 
    int check_num     = 0;
    char *str_rep     = Itoa(num, 16);
    char two_bytes[3] = {0,0,'\0'};
    check_num         = 0;
    
    two_bytes[0] = *str_rep;
    two_bytes[1] = *(str_rep + 1);
    check_num    = Atoi(two_bytes, 16);
  
    return ((check_num - (num >> 24)));    
}
#endif
