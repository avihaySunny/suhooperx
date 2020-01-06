/*******************************************************************************
* Programmer: Avihay Asraf
* WD_Utils_test.c
* File: WD_Utils testing
* Date: ד' יול 24 11:47:22 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include <unistd.h>         /*sleep                                      */
#include <pthread.h>

#include "WD_Utils.h"

int main(void)
{
    size_t interval = 1; 
    size_t threshold = 4; 
    const char *wd_path = "./WDEXE.out"; 
    const char *app_path = "a.out";

    MMI(app_path, wd_path, interval, threshold);
    while (1)
    {
       
    }
    DNR(); 

    return (EXIT_SUCCESS);
}








