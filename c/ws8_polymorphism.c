/****************************************************************************/
/*                                   WS8_polymorphism.c                     */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/

#include <stdio.h>   /* printf, puts             */
#include <stdlib.h>  /* malloc, EXIT_SUCCESS     */
#include <string.h>  /* strcat, strdup           */ 
#include <assert.h>  /* assert  */ 

#define SIZE(x) ((sizeof(x)/sizeof(x[0])))          /*calcs size of array */
#define INT_TO(a)   (a + '0')                       /* turns int to ascii */
#define NUM_OF_TYPES (3)
/*****************************************************************************/    
typedef struct polystruct polystruct_t;               /* for use in struct                       */

static void FreeMemString(polystruct_t *obj);         /* Frees strdup malloc, NUlls ptr to data  */

static void FreeMemRest(polystruct_t *obj);           /* NULL pointers to data                   */

static void AddInt(polystruct_t *obj, int number);    /*Adds an int to int type                  */

static void AddFloat(polystruct_t *obj, int number);  /*Adds float to the float type             */

static void AddString(polystruct_t *obj, int number); /* truncates number to the string          */

static void PrintInt(polystruct_t *obj);                     /*Print int type                           */

static void PrintFloat(polystruct_t *obj);              /*Prints the float type                    */

static void PrintString(polystruct_t *obj);                  /*Prints the string                        */
 
static char *NumToStr(int number);                    /* gets an int and returns a string        */ 

static void InitInt(polystruct_t *arr, int number);   /*Initilizes  int struct object            */

static void InitFloat(polystruct_t *arr, float number); /* Initilizes  float struct object       */

static int InitString(polystruct_t *arr, char *str);  /* Initilize string struct object         */

static void AddnPrintTest(polystruct_t *arr);         /*Tests adding and printing                */
 
static void FreeMemTest(polystruct_t *arr);           /*  Test free_memory function              */

struct polystruct
{
    void *data; 
    void (*add)(polystruct_t *obj, int); 
    void (*print)(polystruct_t *obj); 
    void (*free_memory)(polystruct_t *obj);
}; 

/*****************************MAIN********************************************/
int main (void)
{    
    int val = 5;                       /*initial int   val*/
    float float_val = 9.5;             /*initial float val*/
    char *init_str = "initialzation";  /*initial string val*/
    polystruct_t arr[NUM_OF_TYPES] = {0};
    
    InitInt(&arr[0], val);
    InitFloat(&arr[1], float_val);
    if(InitString(&arr[2],init_str))
    {
        fputs("Try Again, string init fail", stderr); 
        return (EXIT_FAILURE); 
    }
    
    AddnPrintTest(arr); 
    FreeMemTest(arr);   
    return (EXIT_SUCCESS);
}
/******************************TEST FUNCTIONS*********************************/
static void AddnPrintTest(polystruct_t *arr)
{
    int i = 0, number = 0; 
    assert(arr);
    
    for (; i < NUM_OF_TYPES ; ++i)
    {
        printf("data in arr #%d is :", i);
        arr[i].print(&arr[i]);
        puts("");
    }
    
   puts ("Please enter number to add"); 
    if (1 == scanf("%d", &number))
    {       
        for (i = 0; i < NUM_OF_TYPES; ++i)
        {
            printf("data in arr #%d after adding is :", i);
            arr[i].add(&arr[i], number);
            arr[i].print(&arr[i]);
            puts("");
        }
    }
    
    else 
    {
        fputs("SCAN ERROR", stderr);
    }
}

static void FreeMemTest(polystruct_t *arr)
{
    int i = 0; 
    
    assert(arr);
    
    for (; i < NUM_OF_TYPES ; ++i)
    {
        printf("data in arr #%d is :", i);
        arr[i].print(&arr[i]);
        puts("");
    }
     
    for(i = 0; i < NUM_OF_TYPES; ++i)
    {
        arr[i].free_memory(&arr[i]);
        if (NULL == arr[i].data)
        {   
            printf("data in arr slot #%d is NULL and VOID\n",i);
        }  
    } 
}
/***********************************FUNCTIONS*********************************/ 

static void InitInt(polystruct_t *obj, int number)
{
    assert (obj);
    *(int*)&obj->data = number;  
    obj->add = AddInt;
    obj->print = PrintInt;
    obj->free_memory = FreeMemRest;  
}

static void InitFloat(polystruct_t *obj, float number)
{
    assert (obj);
    *(float*)&obj->data = number;  
    obj->add = AddFloat;
    obj->print = PrintFloat;
    obj->free_memory = FreeMemRest;  
}

static int InitString(polystruct_t *obj, char* init_str)
{
    assert (obj);
    obj->data = (char*)malloc(strlen(init_str) + 1);
    
    if (NULL == obj->data)
    {
        fputs("Init MEM FAIL", stderr); 
        return (EXIT_FAILURE) ; 
    }
    
    obj->data = memcpy(obj->data,init_str, strlen(init_str) + 1);  
    obj->add = AddString;
    obj->print = PrintString;
    obj->free_memory = FreeMemString; 
    return (EXIT_SUCCESS);
}

static void FreeMemString(polystruct_t *obj)
{
    assert(obj); 
    free(obj->data);
    obj->data = NULL; 
} 

static void FreeMemRest(polystruct_t *obj)
{
    assert(obj);   
    obj->data = NULL; 
}

static void AddInt(polystruct_t *obj, int number)
{
    assert(obj); 
    *(int*)&obj->data += number; 
}

static void AddFloat(polystruct_t *obj, int number)
{
    assert(obj); 
    *(float*)&obj->data += number;
}

static void AddString(polystruct_t *obj, int number)
{ 
    char *temp_str = NULL;  
    char *new_str = NULL;   
    size_t len1 = 1, len2 = 1;  
   
    assert(obj);
    
    temp_str = NumToStr(number); /*gets a number as a string */
    len1 += strlen((const char*)obj->data); 
    len2 += strlen((const char*)temp_str); 
    new_str = (char*)malloc(len1 + len2);
    memset(new_str, 0, len1 + len2);
    if (NULL == new_str)
    {
        fputs("MEM ERROR", stderr);
        return; 
    }
       
    new_str = strcat(new_str, (const char*)obj->data); 
    if (0 == number) 
    {
        *(new_str + len1) = '0'; 
        *(new_str + len1 + 1) = 0; 
         obj->data = new_str; 
         return; 
    }
    
    free(obj->data); /*releases the old allocation */  
    obj->data =strcat(new_str, (const char*)temp_str); 
    free(temp_str);        
}

/*Counts # of digits, allocates a memory for string + 1 for that size 
  creates that string (from back to front), reversess it and returns*/
static char *NumToStr(int number)
{
    int count = 0, num_copy = 0,i = 0, minus = 0;  
    char *str_head = NULL;
    char *str_runner = NULL; 
    char *str_end = "0";  /* in case number is zero */
    char temp_swap = 0;
      
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
    while (num_copy != 0)
    {
        ++count;
        num_copy /= 10;  
    }
    
    str_head = (char*)malloc(sizeof(char) * (count + minus + 1));
    if (str_head == NULL)
    {
        fputs("MEM ERROR", stderr);
        return NULL; 
    }
    
    if (minus) /*if it's a negetive number*/
    {
        *str_head = '-';
        ++str_head;    
    }
    
    str_runner = str_head;     
    for (; i < count; ++i, ++str_runner)
    {
        *str_runner = (char)INT_TO(number % 10);
        number /= 10;  
    } 
       
    *str_runner ='\0'; 
    str_end = str_runner - 1; 
    str_runner = str_head; 
    for (i = 0; i < (count / 2); ++i)
    {
        temp_swap = *str_end; 
        *str_end = *str_runner; 
        *str_runner = temp_swap; 
        ++str_runner;
        --str_end; 
    }   
    
    return (str_head - minus);
}

static void PrintInt(polystruct_t *obj)
{
    assert(obj); 
    printf("%d\n", *((int*)&obj->data)); 
}

static void PrintFloat(polystruct_t *obj)
{
    assert(obj); 
    printf("%f\n", *((float*)&obj->data));
}

static void PrintString(polystruct_t *obj)
{
    assert(obj); 
    printf("%s\n", (char*)obj->data); 
}

