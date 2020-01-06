/********************************************************************************************************************************************************/
/*                                                          WS3                                                                                         */
/*                                                      Avihay Asraf                                                                                    */                
/*                                                        April 2019                                                                                    */
/********************************************************************************************************************************************************/

#include <stdio.h>          /* printf             */
#include <string.h>         /* strdup,memcopy     */   
#include <stdlib.h>         /* malloc and free    */  
#include <assert.h>         /* assert             */
#include <ctype.h>          /* tolower            */

#include "ws3.h" 

#define SIZE (50)               /* size for LastMan standing */
#define UNUSED(a)    ((void)(a))
 
char *StrToLow(char *str) 
{
    char *head = NULL; 
    assert(str); 
    head = str; 
    
    while(*str != '\0')
    {
        *str = (char)tolower((int)*str);   
        ++str; 
    }
    
    return (head);
}  
char **BufferAppend(char *envp[]) 
{
    char *en_va_buffer = NULL;
    char *dup_temp = NULL; 
    char **en_runner = NULL; 
    char **buffer_index = NULL;
    char **buffer_ind_head = NULL;  
    size_t en_len = 0;
    size_t i = 0; 
    size_t buffer_size = 0;
    size_t temp_len = 0;  
    
    assert(envp);
    en_runner = envp; 
    
    while (*en_runner != NULL)               /* calculates required buffer size */ 
    {
        if(NULL != *en_runner)      
        {
            buffer_size += strlen(*en_runner) + 1;
        }
        
        ++en_len;
        ++en_runner;  
    }
    
    en_runner = envp; 
    en_va_buffer = (char *)malloc(buffer_size * sizeof(char *)); 
    buffer_index = (char **)malloc((en_len + 1) * sizeof(char **));
    
    if(NULL == en_va_buffer) 
    {
        return buffer_ind_head; 
    }
    
    if(NULL == buffer_index)
    {
        return buffer_ind_head; 
    }
    
    *buffer_index = en_va_buffer; 
    buffer_ind_head = buffer_index;   
    
    for(; i < en_len; ++i )             /*creates the buffer using memcopy and the known string length */
    {
        dup_temp = (char*)strdup(*en_runner);
        temp_len = strlen(dup_temp);
        memcpy(*buffer_index, (const char *)StrToLow(dup_temp), temp_len + 1); /* appends the string to the buffer */ 
        
        ++buffer_index;
        *buffer_index = *(buffer_index - 1) + temp_len + 1;     
        ++en_runner;
        
      free(dup_temp);
        dup_temp = NULL;   
    } 
    
    *buffer_index = NULL; 
    return (buffer_ind_head);   
}

void BufferPrint(char **index) 
{
    assert (index);
    
    while(*index != NULL)
    {
        printf("\n %s \n", *index);
        ++index; 
    }  
}

void BufferFree(char **index)
{
    assert (index);
    
    free(*index);
    free(index); 
}

void LastMan(unsigned int group_size)
{
    unsigned int *soldiers = NULL; 
    unsigned int i = 0; 
    
    soldiers = (unsigned int*)malloc(group_size * sizeof(unsigned int)); 
    
    if (NULL == soldiers)
    {
        puts("memory fail");
        return; 
    }
    
    for (; i < group_size - 1 ; ++i)
    {   
        soldiers[i] = i + 1;  
    }
    
    i = 0; 
    
    while (soldiers[i] != i)
    {
        soldiers[i] = soldiers[ soldiers[i] ]; 
        i = soldiers[i]; 
    }
    
    free(soldiers); 
    soldiers = NULL; 
    printf("\nLast man standing for given size is: %u \n", ++i); 
}  
