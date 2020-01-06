/*******************************************************************************
* Programmer: Avihay Asraf
* multi_threaded_counting.c
* File: multi_threaded_counting code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#define DICT_CHAR_SIZE (839620) 
#define HIST_SIZE (256)
#define THREAD_NUM (4) 
#define NUM_OF_COPIES (8)


void SortDictionary (char *buffer, size_t  *dictionary_size, const char *file_path); 




