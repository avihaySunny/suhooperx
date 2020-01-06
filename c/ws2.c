/*        Implementation of the String.h libary for several functions     */ 
/*                      Written by : Avihay Asraf                         */ 
/*                       April 2019                                       */ 

#include <stdio.h>              /*    for printf                  */
#include <stddef.h>             /*    for use of size_t           */ 
#include <assert.h>             /*    for assert                  */
#include <ctype.h>              /*    isalpha, tolower            */  
#include <stdlib.h>             /*    malloc and free             */
#include <string.h>             /*    span cspan                  */

#include "ws2.h"

#define MIN(a,b) ( ((a)<(b)) ? (a):(b) ) 
#define MAX(a,b) ( ((a)>(b)) ? (a):(b) )
#define ASCII_TO(c) (c - '0')                 /* turn ascii to int */ 
#define INT_TO(a)   (a + '0')                 /* turns int to ascii*/

size_t Strlen(const char *str)
{
    const char *ptr = str;  
    assert (str); 
    
    while ( '\0' != *ptr)      
    {
        ++ptr; 
    }
    
    return (ptr - str); 
}

int Strcmp(const char *str1, const char *str2)
{   
    assert(str1);
    assert(str2); 
    
    while ((( *str1 == *str2 ) && 
          ( *str1 != '\0'   )))
    {
        ++str1; 
        ++str2;   
    }
     
    return (int)(*str1 - *str2);    
        
}

int Strncmp(const char *str1, const char *str2,size_t n)
{   
    assert(str1);
    assert(str2); 
    
    while (( *str1 == *str2 ) && 
           ( *str1 != '\0'   ) && 
                (n > 0)     )
    {
        ++str1; 
        ++str2;   
        --n;  
    }
     
     return ((0 != n) ? (0) : (1));     
}

char *Strcpy(char *dest, const char *src)
{
    char *dest_run = dest;
    
    assert(dest);
    assert(src);    
    
    while( *src != '\0')  
    {
        *dest_run = *src; 
        ++dest_run; 
        ++src; 
    }
    
    *dest_run = '\0'; 
    return (dest);  
}

char *Strncpy(char *dest, const char *src, size_t n) 
{
    char *dest_run = NULL; 
      
    assert(dest);
    assert(src);   
    dest_run = dest;
    
    while ((*src != '\0' ) && 
           ( n > 0 )     )   
    {
        *dest_run = *src; 
        ++dest_run; 
        ++src; 
        --n; 
    }
    
    while (n > 0)   
                
    {
        *dest_run = '\0';  
        ++dest_run;  
    }
    
    *dest_run = '\0'; 
    
    return (dest); 

} 

int Strcasecmp(const char *str1, const char *str2)
{
   
    assert(str1);
    assert(str2); 
    
    while( (( tolower(*str1) == tolower(*str2) ) && 
           ( *str1 != '\0'   )))
    {
        ++str1; 
        ++str2;   
    }
     
    return (int)(tolower(*str1) - tolower(*str2));   
        
}

 char *Strchr(const char *str, int c)
 {  
    assert(str); 
    
    while (('\0' != *str) && 
             (c != *str))      
    {
        ++str; 
    }
    
    return ((*str == c) ? ((char *)str) : (NULL));
    
 } 


char *Strdup(const char *s)
{   
    size_t len = 0;
    char *dup_str = (char *)malloc (len);
    
    assert(s); 
    
    len = Strlen(s) + 1;
    return (memcpy(dup_str, s, len));  
}

char *Strcat(char *dest, const char *src)
{
    assert(src);
    assert(dest);
    
    Strcpy (dest + Strlen(dest), src); 
    
    return (dest); 
}

char *Strncat(char *dest, const char *src, size_t n)
{
    memcpy(dest + Strlen(dest), src, n);     
    return(dest); 
}

char *Strstr(const char *haystack, const char *needle)
{
    size_t needle_len = 0;
    assert (needle);
    assert (haystack);
    
    needle_len = Strlen (needle); 
   
    while ((0 != Strncmp(needle, haystack, (int)needle_len)) && 
                                       ('\0' != *haystack) )
    {
        ++haystack;
    }
    
    return (('\0' == *haystack) ? (NULL) : ((char*)haystack));            

}

size_t Strspn(const char *dest, const char *src)
{ 
    size_t spn_size = 0; 
    
    assert (dest);
    assert (src);
   
    while (('\0' != dest ) &&
          (Strchr(src,(int)(*dest)) != NULL))     
    {
        ++spn_size;
        ++dest;      
    }
   
    return spn_size; 
}

char *Strtok(char *str, const char *delim)
{
    static char *tk_head = NULL;
    char *tk_tail = NULL; 
    size_t spn = 0; 
    char zero = 0;
    const char *p_zero = &zero;  
   
    assert(delim);
        
    if (str != NULL) 
    {
        tk_head = str;
        spn = Strspn(tk_head, delim);
        
        if (0 != spn)
        {
        Strncpy(tk_head, p_zero, spn);
        }
         
        tk_head = tk_head + spn; 
         
        return (tk_head);
    }    
    
    spn = Strspn(tk_head, delim);
    
    if (0 != spn)
    {
        Strncpy(tk_head, p_zero, spn);
    }
    
    tk_head = tk_head + spn;
    
    if ('\0' == *tk_head)
    {
        return (NULL); 
    }
    tk_tail = tk_head + strcspn(tk_head, delim); 
    
    if ('\0' == *tk_tail)
    {
        return (NULL); 
    }
    
    *tk_tail = '\0'; 
    ++tk_tail;
    tk_head = tk_tail;  
   
  return(('\0' == *tk_head) ? (NULL) : (tk_head));
}

static int IsSeven(int number)
{ 
    while (number != 0)  
    {    
        if ((number % 10) == 7)
        {    
        return 1; 
        }
        
        number /= 10; 
 }
return 0; 
}
int IsPalindrome(const char  *str)
{
    
    size_t len = 0; 
    char *tail = NULL;
    assert(str);
    
    len = Strlen (str);
    len = (int)(len / 2);
    tail = (char*)(str + Strlen(str) - 1);   
    
    for (; (len > 0) && (*str == *tail); --len, ++str, --tail);     

    return ( (len == 0) ? (1) : (0) ) ; 
}

void Boom(int from, int upto)
{ 
    for(; from <= upto; ++from )
    {
        if((IsSeven(from) || (0 == (from % 7))))
        {
            printf("BOOM\n"); 
        }
        else
        {
            printf("%d\n", from); 
        } 
              
    }
}

void Swap(int **a, int **b)
{
    int *temp = *a; 
    *a = *b; 
    *b = temp;    

}
char *RmSpaces(char *str)              
{    
    char *read_ptr = str;
    char *write_ptr = str;
        
    assert(str);
    
    while ((' ' == *read_ptr) || ('\t' == *read_ptr))
    {
        ++read_ptr;
    }
    
    *write_ptr = *read_ptr;
    
    while ('\0' != *read_ptr)
    {
        if ((0 != isblank((int)*read_ptr)) 
             && (0 != isblank((int)*(read_ptr + 1))))
        {
            ++read_ptr;
        }
        else if ((0 != isblank((int)*read_ptr)) 
                  && ('\0' == (int)*(read_ptr + 1)))
        {
            *write_ptr = '\0';
            ++write_ptr;
            ++read_ptr;
        }
        else
        {
            *write_ptr = *read_ptr;
            if ('\t' == *write_ptr)
            {
                *write_ptr = ' ';
            }
            ++write_ptr;
            ++read_ptr;
        }   
    }
    
    *write_ptr = '\0'; 
    
    return str;                       
}                      


char *StrSum(const char *num1,const char *num2)
{
    size_t len_num1 = 0, len_num2 = 0, len_max = 0, len_min = 0;
    char *result = NULL;
    char *r_head = NULL;
    const char *res_sum = NULL;             /* const for func argument */ 
    int carry = 0, sum = 0;   
    
    assert(num1);
    assert(num2);
    
    len_num1 = Strlen(num1);
    len_num2 = Strlen(num2); 
    len_max = MAX(len_num1, len_num2);
    len_min = MIN (len_num1, len_num2); 
    
    result = (char*)malloc(len_max + 2);   /*add 2, 1 for '\0' one for carry */  
    r_head  = result;
   
    if(NULL == result)
    {
        return NULL;    
    }
    
    num1 += len_num1 - 1; 
    num2 += len_num2 - 1;
    result += (len_max + 1); 
    *result  = '\0';
    --result; 
    
    for(; len_min > 0 ; --len_min, --len_max )     
    {
        sum = ASCII_TO(*num1) + ASCII_TO(*num2) + carry; 
        carry = sum / 10; 
        *result = INT_TO(sum % 10); 
        
        --result; 
        --num1;
        --num2;
    }
     
    (len_num1 > len_num2) ? (res_sum = num1): (res_sum = num2); /*sets the larger number for 2nd loop addition*/   
     
     for (; len_max > 0 ; --len_max)
     {
        sum = ASCII_TO(*res_sum) + carry; 
        carry = sum / 10; 
        *result = INT_TO(sum % 10); 
        --result; 
        --res_sum; 
     }
     
     if(0 == carry)
     {
        *result = ' ';
     }
     else
     {
         *result = INT_TO(carry);
     } 
     
     return (r_head);
}

void StrToLow(char *str)
{
    while(*str != '\0')
    {
        *str = (char)tolower((int)*str);   
        ++str; 
    }
}

