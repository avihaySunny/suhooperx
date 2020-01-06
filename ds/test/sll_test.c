/*******************************************************************************
* Programmer: Avihay Asraf
* sll_test.c
* File: sll testing
* Date: ב' מאי 13 16:41:56 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */

#include "sll.h"

/*--------------------TEST DESCRYPTION-----------------------------------------
*               1. Tests Creating a node's head.         
*               2. Tests Find function using ForEach and a given function. 
*                  one search for data existing in list and one test for without. 
*               3. insert before -> inserts a new link before node and checks if  
*                  the known data is where expected. 
*               4. remove after - removes a known node and checks known position  
*                  for data. 
*               5. Remove current head and checks if been removed. 
*               6. Setup list and flips it - checks if fliped. 
*               7. Sets up a list with an intersection and finds it. 
*               8. Sets up looped list - and checks for loop. 
*-----------------------------------------------------------------------------*/

static int TestCreateSLL(void); 
static int TestSLLFindTest(void);
static int SSLFinder(const void *person, const void *param);
static int TestInsertBefore(void);
static int TestRemoveCurrent(void);
static int TestRemoveAfter(void);
static node_t *SLLFetch(node_t *head, size_t indx); /*Returns i element in list*/
static int TestSLLFlip(void); 
static int TestSLLIntersection(void);
static int TestSLLLoop(void);

/*static int PrintPerson(void *data, void *param); function for printing struct*/ 
/*--------------------------------------------------------------------------*/
 typedef struct person
{
    char name[25];
    int age; 
    float height;  
} person_t; 

 person_t frank[] =  {{"frank", 30, 1.8      },
                      {"franky", 31, 1.75    },                  
                      {"frankol", 32, 1.7    },
                      {"frankish", 33, 1.65  },
                      {"frankila", 34, 1.6   },
                      {"frankilla", 35, 1.55 },
                      {"frankgzila", 3, 1.5  },
                      {"frankgzilla", 3, 1.45},
                      {"frankgdila", 3, 1.4  },
                      {"franklast", 10, 1.35}};

/*--------------------MAIN------------------------------------------------*/
int main(void)
{   
    size_t fail_count = 0; 
    size_t num_of_tests = 8; 
   
    if(0 == TestCreateSLL())
    {
        ++fail_count; 
        puts(RED"TEST CREATE SSL FAIL"RESET);
    }
    if(0 == TestSLLFindTest())
    {
        ++fail_count;
        puts(RED"TEST FIND SSL FAIL"RESET);
    }  
    if(0 == TestInsertBefore())
    {
        ++fail_count;
        puts(RED"TEST INSERT BEFORE SSL FAIL"RESET);
    }
    if(0 == TestRemoveAfter())
    {
        ++fail_count;
        puts(RED"TEST REMOVE AFTER SSL FAIL"RESET);
    }
    if(0 == TestRemoveCurrent())
    {
        ++fail_count;
        puts(RED"TEST REMOVE CURRENT SSL FAIL"RESET);
    }
    if(0 == TestSLLFlip())
    {
        ++fail_count;
        puts(RED"TEST FLIP SSL FAIL"RESET);
    }
    if(0 == TestSLLIntersection())
    {
        ++fail_count;
        puts(RED"TEST Intersection SSL FAIL"RESET);
    }
    if(0 == TestSLLLoop())
    {
        ++fail_count;
        puts(RED"TEST LOOP SSL FAIL"RESET);
    }
    
    printf(CYAN"Test Performed : %ld\n"RESET,num_of_tests); 
    puts("-----------------------------");
    printf(GREEN"Test SUCCESS : %ld\n"RESET,num_of_tests - fail_count); 
    printf(RED"Test FAIL : %ld\n"RESET,fail_count); 
    
    return (EXIT_SUCCESS);
}

static int TestCreateSLL(void)
{
    size_t i = 0; 
    node_t  *head = SLLCreateNode(&frank, NULL); 
    
    for (i = 0; i < 10; ++i)
    {  
        SLLInsertAfter(head,SLLCreateNode(&frank[i], NULL));
    }
    
    if (11 == SLLCount(head))
    {
        SLLFreeAll(head);
        head = NULL; 
        
        return 1;  
    }
    
    SLLFreeAll(head);
    head = NULL; 
    
    return 0; 
}

static int TestInsertBefore(void) 
{
    size_t i = 0; 
    node_t  *head = SLLCreateNode(&frank, NULL); 
    node_t *tmp = head; 
    
    for (i = 1; i < 4; ++i)
    {  
        tmp = SLLInsertAfter(head,SLLCreateNode(&frank[i], NULL));
    }
    
    SLLInsertBefore(head, SLLCreateNode(&frank[7],NULL));         
    
    if (head->data == &frank[7])
    {
        SLLFreeAll(head);
        head = NULL; 
        
        return 1 ;  
    } 
    
    SLLFreeAll(head);
    head = NULL;
    UNUSED(tmp);
    return 0; 
}

static int TestRemoveAfter(void)
{
    size_t i = 0; 
    void *data = NULL;  
    node_t  *head = SLLCreateNode(&frank, NULL); 
    node_t *tmp = head; 
    
    for (i = 1; i < 7; ++i)
    {  
        tmp = SLLInsertAfter(head,SLLCreateNode(&frank[i], NULL));
    }
    
    tmp = SLLFetch(head ,2);
    data = tmp->next->data; 
    tmp = SLLRemoveAfter(head);
    free(tmp);
    tmp = NULL; 
    
    if (data != SLLFetch(head,3)->data)
    {
        SLLFreeAll(head);
        head = NULL; 
        
        return 1 ;   
    }
    
    SLLFreeAll(head);
    head = NULL; 
    
    return 0;
}

static int TestRemoveCurrent(void)
{
    size_t i = 0; 
    node_t  *head = SLLCreateNode(&frank, NULL); 
    node_t *tmp = head; 
    void *data = NULL; 
    
    for (i = 1; i < 7; ++i)
    {  
        SLLInsertAfter(head,SLLCreateNode(&frank[i], NULL));
    }

    data = head->data;
    tmp  = SLLRemoveCurrent(head); 
    free(tmp);
    tmp  = NULL; 
    
    if (data != head->data)
    {
        SLLFreeAll(head);
        head = NULL; 
        
        return (1) ;   
    }
    
    SLLFreeAll(head);
    head = NULL; 
   
    return (0);
}

static int TestSLLFindTest(void)
{
    size_t i = 0; 
    
    char *indata = "frankish";  
    char *notindata = "hello"; 
    person_t *found = NULL;     
    
    node_t  *head = SLLCreateNode(&frank, NULL); 
    node_t *where = NULL; 
    
    for (i = 0; i < 10; ++i)
    {  
        SLLInsertAfter(head,SLLCreateNode(&frank[i], NULL));
    }
    
    where = SLLFind(head, SSLFinder,indata);
    found = (person_t*)where->data; 
    
    if (0 == strcasecmp(found->name, indata) && 
       (NULL == SLLFind(head, SSLFinder,notindata)))
    {
        SLLFreeAll(head);
        head = NULL; 
        
        return (1); 
    }

    SLLFreeAll(head);
    head = NULL; 
    
    return (0);  
}

static int TestSLLFlip(void)
{
    size_t i = 0; 
    static int arr[30] = {0}; 
    node_t  *head = SLLCreateNode(arr, NULL); 
    node_t *new_head = NULL;
    node_t *tmp = NULL; 
    
    for (i = 1; i < 30; ++i)
    {
        arr[i] = i;
    }
    
    for (i = 0; i < 10; ++i)    /*Creates List*/
    {  
        SLLInsertAfter(head, SLLCreateNode(&arr[i], NULL));
    }
     
    new_head = SLLFlip(head);
    tmp = SLLFetch(new_head, 2);
    for (i = 2 ; i < 10; ++i)
    { 
         if (arr[i] != *(int*)tmp->data) 
         {
            puts("shit");
            SLLFreeAll(new_head); 
            new_head = NULL; 
            return (0); 
         } 
         
     tmp = tmp->next;  
    }
    
    SLLFreeAll(new_head); 
    head = NULL; 
    
    return (1);
}

static int TestSLLIntersection(void)
{   
    size_t i      = 0;
    static int arr[50]   = {0};
    node_t *first = NULL; 
    node_t *sec   = NULL; 
    node_t *intersection = NULL;
    node_t *intersected = NULL;    
    node_t *tmp = NULL; 
    
    for (i = 0; i < 50; ++i) /*set up for  lists*/
    {
         arr[i] = i;
    }
    
    first = SLLCreateNode(&arr, NULL);
    sec   = SLLCreateNode(&arr[25], NULL); 

    for (i = 1; i < 20; ++i)
    {
        SLLInsertAfter(first,SLLCreateNode(&arr[i], NULL));
        SLLInsertAfter(sec,SLLCreateNode(&arr[i + 25], NULL));
    }
    
    
    tmp = SLLFetch(sec, 5)->next; /*keeps next for fixing*/
    /*------Creates Intersection---------- */
    intersected = SLLFetch(first, 15); 
    SLLFetch(sec, 5)->next = SLLFetch(first, 15);     
    intersection = SLLFindIntersection(first, sec);
    /*------Fixes Intersection for freeing------------*/
    SLLFetch(sec, 5)->next = tmp;  
    if(intersection == intersected)
    {
        SLLFreeAll(first); 
        SLLFreeAll(sec);  
        return (1);
    }
 
    return (0);      
}

static int TestSLLLoop(void)
{
    size_t i = 0;
    static int arr[50]   = {0};
    node_t *list = NULL;     
    node_t *tmp = NULL; 
    list = SLLCreateNode(arr, NULL);
    for (i = 0; i < 50; ++i)
    {
         arr[i] = i;
    }
    
    for (i = 1; i < 20; ++i)
    {
        SLLInsertAfter(list,SLLCreateNode(&arr[i], NULL));
    }
    
    tmp = SLLFetch(list, 12)->next;        /*for safekeeping and freeing*/
    SLLFetch(list, 12)->next = SLLFetch(list, 4);
    i = SLLHasLoop(list);
    SLLFetch(list, 12)->next = tmp;
    SLLFreeAll(list); 
    list = NULL; 
   
    return i;  
}

static int SSLFinder(const void *person, const void *param)
{
    
    person_t *temp = (person_t*)person;  
    UNUSED(param);
    return(0 == strcasecmp(temp->name, (const char*)param)); 
}

static node_t *SLLFetch(node_t *head, size_t indx)
{
    size_t i = 0; 
    while((NULL != head) && (i != indx))
    {
        ++i;
        head = head->next;     
    }
    
    return (head);
}


