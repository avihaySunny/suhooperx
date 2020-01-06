/***************************************************************************/
/*                                      WS3 Test                           */
/*                                    Avihay Asraf                         */              
/*                                    April 2019                           */
/*******************q*******************************************************/
#include <stdio.h>          /* printf             */
#include <string.h>         /* strdup,memcopy     */   
#include <stdlib.h>         /* malloc and free    */  
#include <assert.h>         /* assert             */
#include <ctype.h>          /* tolower            */

                       
#define UNUSED(a)    ((void)(a))
#define ESC (27)
#include "ws3.h" 

 void TestLastMan(unsigned int group_size);
 void TestBuffer(char **envp);

int main(int argc, char *argv[], char *envp[])
{ 
    unsigned int group_size = 0;
    unsigned ch = 0; 
    group_size = (unsigned int)atoi(argv[1]);
   
    puts("for testing environment enter 1\n, for last man enter 2\n otherwise press ESC \n");
    
    switch (ch = getchar())
    { 
        case '1':
        {   
            TestBuffer(envp);  
            break; 
        }
        case '2':
        {
            TestLastMan(group_size); 
            break;   
        } 
     }
     
    UNUSED (envp);
    UNUSED (argc);
   
    return EXIT_SUCCESS;        
}   
void TestBuffer(char **envp)
{
    char **indx = BufferAppend(envp); 
    BufferPrint(indx);    
    BufferFree(indx);
    indx = NULL; 
}

void TestLastMan(unsigned int group_size)
{
    LastMan(group_size); 
}
