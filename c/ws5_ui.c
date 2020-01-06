/*********************************************************************/
/*                       WS5_UI.c                                    */
/*                        Avihay Asraf                               */                
/*                       April 2019                                  */
/*********************************************************************/
#include <string.h>         /* strlen                */
#include <stdio.h>          /* printf, puts, scanf   */
#include <assert.h>         /* assert                */

#include "ws5_file.h" 

#define OP_NUM ((sizeof(oper_arr)/sizeof(oper_arr[0])))              /* # of operation available on logger */
#define BASE_LEN (500)          /*  max input length available        */
#define UNUSED(a)   ((void)(a)) /* for unusued variables              */

typedef struct commands                /*type Struct for commands */
{
    const char *com_str; 
    int (*cmp_command)(const char*, char*, size_t); 
    log_state_t (*com_caller)(const char*, const char*); 
}   commands_t[];
        
 /*Initializing constant commands  - string name, compare func, operation func*/
  
static const commands_t oper_arr =  {{"-remove",LogCommCmp , LogFileRemove },  
                                    {"-count" , LogCommCmp , LogLineCount  },
                                    {"<"      , LogCommCmp , LogPrepend    },
                                    {"-help"  , LogCommCmp , LogPrintHelp  },
                                    {"-exit"  , LogCommCmp , ExitLog       }, 
                                      /*Append func must be last! */  
                                    {""      , VeryTrue   , LogAppend     }};

log_state_t ExitLog(const char* input, const char* mess)
{ 
   UNUSED(input);
   UNUSED(mess);
   
   return EXIT;
}

int LoggerEventLoop(const char *file_name)
{
    char input[BASE_LEN]=" ";
    unsigned int i = 0;
    size_t len = 0; 
    log_state_t run_stat = OK; 
    
    assert(file_name);
    
    puts("Please Enter text to append / command or '-help' for help");
    while (run_stat != EXIT)
    {
        run_stat = scanf("%s", input);      
        for(i = 0; i < OP_NUM; ++i)
        {  
             len = strlen(oper_arr[i].com_str); 
             if(oper_arr[i].cmp_command(oper_arr[i].com_str, input, len)) 
             {
                run_stat = oper_arr[i].com_caller(file_name, input + len );
                break;        
             }             
        } 
        
        if (run_stat != OK)
        {
           return run_stat;   
        }
    }  
    
    return (run_stat);
}

int LogCommCmp(const char *com, char *input,size_t len) 
{
    assert(com);
    assert(input);
    
    return(OK == strncmp(com, (const char*)input, len));
}

int VeryTrue(const char *com, char *input, size_t len)
{
    UNUSED(com);
    UNUSED(input);
    UNUSED(len);
    
    return 1; 
}

log_state_t LogPrintHelp(const char* file_name, const char *input) 
{
    puts("Here to help\n");
    puts("Enter -remove to delete file\n");
    puts("Enter -count to count lines\n");
    puts("Enter < before text to pre-append\n");
    
    UNUSED(input); 
    UNUSED(file_name);
    return OK;
}

int main(int argc, char *argv[])
{ 
    char name_of_file[200] = {0};   /* in case of no file name was entred */ 
    const char *file_name = NULL;   
    enum status end_state = OK;
    assert(argv);    
    if (NULL == argv[1])
    {
        puts("No file name detected \n"); 
        puts("Please enter file name\n "); 
        end_state = scanf("%s", name_of_file);      
        file_name = name_of_file;   
    }
    
    else 
    {
        file_name = (const char *)argv[1];
    } 
    
    end_state = LoggerEventLoop(file_name); /*runs main program, returns state */
    if (OK != end_state)
    {
        return end_state;
    }     
    
    UNUSED(argc);
    return OK;
}
