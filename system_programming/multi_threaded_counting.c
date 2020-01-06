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
#include <pthread.h>        /* pthreads                                 */
#include <ctype.h>          /* isalpha                                  */

#define DICT_CHAR_SIZE (839620) 
#define UP_LIMIT (25)
#define HIST_SIZE (256)
#define THREAD_NUM (4) 
#define NUM_OF_COPIES (8)

typedef struct 
{
    char *arr_ptr; 
    int  *histgram_ptr; 
    size_t arr_size; 
    size_t thread_num;     
} count_bundle_t; 

/* ---------------------------------------------------------------- */
/*loads dictionary into buffer (only characters) */ 
static void DictionaryBufferLoader(char *buffer, size_t *char_count, const char *file_path);
/* fill empty histogram with instances from buffer */
static void CountInstancesToHist(char *arr, size_t arr_size, int *histogram);
/* sort fucntion for each thread */
static void *CounterThread(void *arg);
/* refills buffer in a sorted manor from histogram      */
static void RewriteBufferFromHist(int *combined_hist,char *buffer );
/* creates data bundle need for each thread             */
static void BundleInit(count_bundle_t *bundles, char *buffer, int *histograms, size_t count);
/*  copies dictionary for               */
static void CopyDictionary(char *buffer, size_t num_of_copies, size_t *count); 
/* Sums all histograms                   */
static void MergeHistogram(int *histogram);

/* ---------------------------------------------------------------- */
#if 0
static pthread_mutex_t increment_lock = PTHREAD_MUTEX_INITIALIZER; 
#endif 
/* ---------------------------------------------------------------- */
void SortDictionary (char *buffer, size_t  *dictionary_size, const char *file_path)
{
    size_t i = 0; 
    count_bundle_t bundles[THREAD_NUM] = {0}; 
    int histogram[THREAD_NUM * HIST_SIZE] = {0}; 
    pthread_t counter_thread[THREAD_NUM] = {0}; 
 
    DictionaryBufferLoader(buffer, dictionary_size, file_path);
    CopyDictionary(buffer, NUM_OF_COPIES, dictionary_size);
    BundleInit(bundles,buffer, histogram, *dictionary_size);
    
    for (i = 0; i < THREAD_NUM; ++i)
    {
        while (0 != pthread_create(&counter_thread[i], NULL, CounterThread, (void*)(bundles + i)))
        {
            puts("thread creation failed");
        }
    }
    for (i = 0; i < THREAD_NUM; ++i)
    {
        pthread_join(counter_thread[i], NULL);  
    } 
    
    MergeHistogram(histogram);
    RewriteBufferFromHist(histogram, buffer);
}

static void BundleInit(count_bundle_t *bundles, char *buffer, int *histograms, size_t count)
{
    size_t i = 0; 
    for (i = 0; i < THREAD_NUM; ++i)
    {
        bundles[i].arr_ptr = buffer + i * (count / THREAD_NUM);
        bundles[i].arr_size = count / THREAD_NUM; 
        bundles[i].histgram_ptr = histograms + i * HIST_SIZE;
        bundles[i].thread_num = i; 
    }
}
/* ---------------------------------------------------------------- */
static void DictionaryBufferLoader(char *buffer, size_t *char_count, const char *file_path)
{
    FILE *dictionary = NULL;  
    int c = 0; 
    assert(buffer);

    dictionary = fopen(file_path, "r");
    if (NULL == dictionary)
    {
        return;
    }

    while (EOF != (c = fgetc(dictionary)))
    {
        if(isalpha(c) && c != 0)
        {
            *buffer = (char)c; 
            ++buffer; 
            ++*char_count; 
        }
    }

    fclose(dictionary);
}
/* ---------------------------------------------------------------- */
static void CountInstancesToHist(char *arr, size_t arr_size, int *histogram)
{
    size_t i = 0;
    assert(arr);

    for (i = 0; i < arr_size; ++i)
    {     
        ++histogram[(int)arr[i]];
    }
}
/* ---------------------------------------------------------------- */
static void *CounterThread(void *arg)
{
    count_bundle_t *bundle = arg; 
    int *hist = bundle->histgram_ptr; 
    char *buff = bundle->arr_ptr; 
    size_t arr_size = bundle->arr_size;
    CountInstancesToHist(buff, arr_size, hist); 

    return arg; 
}
/* ------------------------------------------------------------------ */
static void RewriteBufferFromHist(int *combined_hist,char *buffer)
{
    size_t i = 0; 
    char *buffer_runner = buffer; 

    assert(buffer); 
    assert(combined_hist);

    for (i = 0; i < HIST_SIZE; ++i)
    {
        while (combined_hist[i] > 0)
        {
            *buffer_runner = i; 
            ++buffer_runner; 
            --combined_hist[i]; 
        }
    }
}
/* ------------------------------------------------------------------- */
static void MergeHistogram(int *histogram)
{
    size_t i = 0;
    size_t j = 0; 
    int *main_hist = histogram; 
    
    assert (histogram);  
    
    for (i = 1; i < THREAD_NUM; ++i)
    {
        for (j = 0; j < HIST_SIZE; ++j)
        {
            main_hist[j] += histogram[j + i * HIST_SIZE];
        }
    }
}
/* ------------------------------------------------------------------- */
static void CopyDictionary(char *buffer, size_t num_of_copies, size_t *count)
{
    size_t i = 0; 
    char *buffer_head = buffer; 
    buffer += *count; 
    
    assert(buffer);
    
    for (i = 0; i < num_of_copies - 1; ++i)
    {
        memcpy(buffer, buffer_head, *count); 
        buffer += *count;  
    }  

    *count *= NUM_OF_COPIES; 
}
