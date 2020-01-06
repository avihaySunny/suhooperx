/***************************************************************/
/*                       WS5_File.c                              */
/*                        Avihay Asraf                         */                
/*                       April 2019                             */
/****************************************************************/

#include <string.h>  /*strcmp, strlen..         */
#include <stdlib.h>  /* EXIT_SUCCESS/FAIL       */  
#include <stdio.h>   /* fopen, printf..         */
#include <assert.h>  /* assert                   */

#include "ws5_file.h"

#define OP_NUM (sizeof(oper_arr)/sizeof(oper_arr[0]))     /* Number of operations available on logger */
#define BASE_LEN (1000)                                   /* max input length available               */
#define FAIL (-1)       
#define UNUSED(a)    ((void)(a))                          /* for unusued variables                    */

log_state_t LogFileRemove(const char* file_name, const char *input)
{
    int state_val = OK; 
    
    assert(file_name); 
    state_val = remove(file_name);
    
    if(-1 == state_val)
    {
        fputs("No File to remove \n", stderr);
        return REMOVE_FAILED;
    }

    UNUSED (input);
    UNUSED (file_name);
    
    return OK; 
}

log_state_t LogAppend(const char* file_name, const char *input)
{
    int state_val = OK; 
    FILE *myfile = NULL; 
    
    assert(file_name);
    assert(input);
    
    myfile = fopen(file_name,"a");   
    if (myfile == NULL)
    {
        fputs("Can't seem to find file \n", stderr);
        return NO_FILE; 
    }
    
    state_val = fputs(input, myfile);   
    if (EOF == state_val)
    {   
        fputs("Error in File \n", stderr);
        return FILE_FAIL; 
    }
    
    state_val = fputc('\n',myfile);
    if (EOF == state_val)
    {
        fputs("Error in File \n", stderr);
        return FILE_FAIL; 
    }
    
    state_val = fclose(myfile);
    if (EOF == state_val)
    {
        fputs("Problem closing File \n", stderr);
        return FILE_FAIL; 
    }
    
    return OK;   
}

log_state_t LogLineCount(const char* file_name, const char *input)
{
    int state_val = 0, count = 0;           /*state_val holds error # */
    FILE *myfile = NULL; 
    char c = '0'; 
    
    assert(file_name);
    myfile = fopen(file_name,"r");
    if (NULL == myfile)                    /*checks fopen works properly */ 
    {
        fputs("NO FILE \n", stderr);
        return NO_FILE; 
    }
    while (EOF != c)                        /*checks for end of file*/
    {
        c = fgetc(myfile); 
        
        if (c =='\n')
        {
          ++count;             
        } 
    } 
    
    state_val = fclose(myfile);   
    if (EOF == state_val)                  /*check file has been closed */
    {
        fputs("Error closing file \n", stderr);
        return FILE_FAIL;
    }
   
    printf("Number of line is : %d \n ",count);
    UNUSED(input); 
    return OK; 
}

log_state_t LogPrepend(const char* file_name, const char *input)
{
    int state_val = 0;
    char c = '0'; 
    
    FILE *new_file = fopen("newfile.txt","w"); /*creates new file to write to */
    FILE *old_file = NULL; 
    
    assert (input);
    assert (file_name);
    if (NULL == new_file)       /*checks fopen works properly */ 
    {
        fputs("NO FILE \n", stderr);
        return FILE_FAIL;    
    }
    
    old_file = fopen(file_name,"r");
    if (NULL == old_file)       /*checks fopen works properly */ 
    {
        fputs("Unable to open file \n", stderr);
        return FILE_FAIL;    
    }
     
    state_val = fputs(input, new_file);  /*writes input to new file */
    if (EOF == state_val)                    /*check for error          */
    {
       fputs("Unable to write to file \n", stderr);
       return FILE_FAIL; 
    }
     
    state_val = fprintf(new_file, "%s", "\n");    /* goes to next line */
    if (EOF == state_val)                         /*check for error    */
    {
       fputs("Unable to write to file \n", stderr);
       return FILE_FAIL; 
    }
        
    state_val = fclose(new_file);                /* closes new file  */
    if (EOF == state_val)
    {
       fputs("Unable to close file \n", stderr);
       return FILE_FAIL; 
    }
    
    new_file = fopen("newfile.txt","a");  
    if (NULL == new_file)
    {
        fputs("Unable to open to file \n", stderr);
       return FILE_FAIL;    
    }
 
    c = fgetc(old_file);
    while (c != EOF )                       /*appends old file to new file*/
    {  
        fputc(c, new_file);    
        c = fgetc(old_file);
    }     
        
    state_val = fclose(old_file);
    if(EOF == state_val)
    {
        fputs("Unable to close file \n", stderr);
        return FILE_FAIL;
    }
    
    state_val = remove(file_name);          /*removes old file */
    
    if(REMOVE_FAILED == state_val)
    {
        return REMOVE_FAILED; 
    } 
    
    rename("newfile.txt",file_name);        /*gives new file an old name */
    state_val = fclose(new_file);
    if (EOF == state_val)
    {
       fputs("Unable to close file \n", stderr);
       return FILE_FAIL; 
    }
    
    return  OK; 
}


