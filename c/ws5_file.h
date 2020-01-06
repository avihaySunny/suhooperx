/***************************************************************/
/*                       WS5_File.h                            */
/*                        Avihay Asraf                         */                
/*                       April 2019                            */
/***************************************************************/
#include <string.h>   /*  strlen        */

#ifndef __WS5__FILE_H__ 
#define __WS5__FILE_H__  
       
typedef enum status         /*Error list for functions to return */
{   
    OK,             /* Succes                     */
    FAIL,           /* General fail               */     
    NO_FILE,        /* Unable to find file        */
    REMOVE_FAILED,  /* Unable to remove file      */
    EXIT,           /* status for exiting program */
    FILE_FAIL,      /* Unable to open/close file  */
    RENAME_FAIL,    /* Unable to find name        */
    INPUT_FAIL,      /* scanf failure              */
    REMOVE_SUCCESS
}log_state_t;
                       /*ALL ENUM function return OK or error from above */ 

log_state_t LogFileRemove(const char* file_name, const char *input);   /*removes the file worked on, doesn't end program  */ 

log_state_t LogPrepend(const char* file_name, const char *input);      /*Prepends following text                          */
 
log_state_t LogAppend(const char* file_name, const char *input);       /* Appends following text                          */

log_state_t LogLineCount(const char* file_name, const char *input);    /*     Count # of lines                            */ 

log_state_t LogPrintHelp(const char* file_name, const char *input);    /* Prints help message                             */ 
        
int LogCommCmp(const char *com, char *input, size_t len);              /* Default compare function for operations         */

log_state_t ExitLog(const char* input, const char* mess);              /* Returns EXIT State thus exiting program         */

int LoogerEventLoop(const char *file_name);                            /* Main program runs here                          */

int VeryTrue(const char *com, char *input, size_t len);                /* Always returns true, for a compare function     */

#endif
