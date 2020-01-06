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
#include <ctype.h>          /*is lower */
#include "../include/multi_threaded_counting .h" 

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"

static void PrintBuffer(char *buffer, size_t buffer_size);
static int IsSorted(char *buffer, size_t count);

int main ()
{
    const char *dic_path = "/usr/share/dict/american-english"; 
    size_t count = 0; 
   
    char *buffer = malloc(DICT_CHAR_SIZE * NUM_OF_COPIES);    
    if (NULL == buffer)
    {
        return EXIT_FAILURE;
    }

    SortDictionary(buffer, &count, dic_path); 
    puts("buffer is sorted :");
    IsSorted(buffer, count) == 1  ? puts ("SORTED") : puts("NOT SORTED"); 
    printf("Number of characters sorted : %ld \n", count);
    
    puts ("Enter to print sorted dictionary in colors (Y/N) :"); 
    if ('y' == tolower(getchar()))
    {
        PrintBuffer(buffer, count); 
        puts("\n");
    }
    
    free(buffer);
    return EXIT_SUCCESS;
}

static void PrintBuffer(char *buffer, size_t buffer_size)
{
    size_t i = 0; 
    for (i = 0; i < buffer_size ; i +=3)
    {
        printf(MAGENTA "%c", *buffer); 
        printf(YELLOW "%c", *(buffer + 1));
        printf(CYAN "%c", *(buffer + 2));
         
        buffer = buffer + 2; 
    }
}
static int IsSorted(char *buffer, size_t count)
{
    size_t i = 0; 
    for (i = 0; i < count - 1; ++i)
    {
        if (buffer[i] > buffer[i + 1])
        {
            return 0; 
        } 
    }

    return 1; 
}