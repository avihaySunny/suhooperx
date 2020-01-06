/*******************************************************************************
* Programmer: Avihay Asraf
* shufflensort.c
* File: shufflensort code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <strings.h>         /* memcpy                                   */
#include <string.h>         /* memcpy                                   */
#include <pthread.h>    
#include "../ds/include/sorting.h"
#include "shufflensort.h"

typedef struct 
{
    char **wrd_list_ptr; 
    int (*is_before)(const char*, const char*);

} bundle_t; 
static void Merge(void *arrA, void *arrB, size_t size, size_t nmembA, size_t nmembB, 
                    int(*cmp)(const void*, const void*), void *arrAux);
static void MergeDictionary(char *str_list[], size_t size);
static void DictionaryWordLoader(char *buffer, char *wrd_ptrs[], size_t *word_count);
static void ShuffleStrings(char *wrd_ptr_list[]);
static void *ShuffleThread(void *arg);
static void SwapPtr(char **str1, char **str2);
static void MultiplyPtrArr(char *wrd_ptr_list[], size_t *count); 
static int IsBefore (const void *wordA, const void *wordB);
static void *SorterThread(void *arg);
static void ThreadCreateAndManage(pthread_t *shufflethreads, pthread_t *sorter_threads, char *wrd_buff_ptrs[]);
static void write_err_log(const char *err); 

/* ----------------------------------------------------------------- */
void ShuffleAndSort (char *wrd_buff_ptrs[], char *buffer, size_t *count)
{
    pthread_t shuffle_thread[SHUFFLE_THREAD_NUM] = {0}; 
    pthread_t sorter_thread[SORTER_THREAD_NUM] = {0};   

    DictionaryWordLoader(buffer, wrd_buff_ptrs, count); 
    MultiplyPtrArr(wrd_buff_ptrs, count);
    ThreadCreateAndManage(shuffle_thread, sorter_thread, wrd_buff_ptrs);
    MergeDictionary(wrd_buff_ptrs, *count); 
}
/* -------------------------------------------------------------------------------- */
static void DictionaryWordLoader(char *buffer, char *wrd_ptrs[], size_t *word_count)
{
    FILE *dictionary = NULL;  
    size_t len = 0; 
    char word_buff[UPPER_LIMIT] = {0}; 

    assert(buffer);
    assert(wrd_ptrs);

    dictionary = fopen("/usr/share/dict/american-english", "r");
    if (NULL == dictionary)
    {
        write_err_log("open dictional fail"); 
        return;
    }

    while (NULL != fgets(word_buff, UPPER_LIMIT, dictionary))
    {
        len = strlen(word_buff);
        memcpy(buffer, word_buff, len);
        wrd_ptrs[*word_count] = buffer;  
        buffer = buffer + len + 1;
        ++*word_count; 
    }

    fclose(dictionary);
}
/* --------------------------------------------------------------- */
static void ShuffleStrings(char *wrd_ptr_list[])
{
    size_t size = DIC_WRD_NUM;
    size_t i = 0; 

    for (i = 0; i < size - 1; i++)
    {
        int j = i + (rand() % (DIC_WRD_NUM - i)); 
        SwapPtr(&wrd_ptr_list[i], &wrd_ptr_list[j]);
    }
}
/* ------------------------------------------------------------------ */
static void SwapPtr(char **str1, char **str2)
{
    char *tmp = *str1; 
    *str1 = *str2;
    *str2 = tmp;    
}
/* ------------------------------------------------------------------- */
static void *ShuffleThread(void *arg)
{
    char **wrd_list_ptr = arg;  
    assert(arg); 

    ShuffleStrings(wrd_list_ptr);
    return arg; 
}
/* -------------------------------------------------------------------- */
static void MultiplyPtrArr(char *wrd_ptr_list[], size_t *count)
{
    size_t i = 0; 
    char **base_ptr = wrd_ptr_list; 
    wrd_ptr_list = wrd_ptr_list + DIC_WRD_NUM; 

    for (i = 0; i < NUM_OF_COPIES - 1; ++i)
    {
        memcpy(wrd_ptr_list, base_ptr, sizeof(char*) * DIC_WRD_NUM);
        wrd_ptr_list = wrd_ptr_list + DIC_WRD_NUM; 
    }

    *count *= NUM_OF_COPIES; 
}

/* ---------------------------------------------------------------------------------- */
static int IsBefore (const void *wordA, const void *wordB)
{
    return strcmp(*(char**)wordA, *(char**)wordB);
}
/* ------------------------------------------------------------------------------------- */
static void *SorterThread(void *arg)
{
    assert(arg); 

    qsort(arg, DIC_WRD_NUM * 2, sizeof(char *), IsBefore); 
    return arg;
}
/* ------------------------------------------------------------------------------------------------------------ */
static void ThreadCreateAndManage(pthread_t *shuffle_threads, pthread_t *sorter_threads, char *wrd_buff_ptrs[])
{
    size_t i = 0; 

    assert(shuffle_threads);
    assert(sorter_threads); 
    assert(wrd_buff_ptrs); 

    for (i = 0; i < SHUFFLE_THREAD_NUM; ++i)
    {
        while(0 != pthread_create(shuffle_threads + i, NULL, &ShuffleThread, wrd_buff_ptrs + i * DIC_WRD_NUM))
        {
            pthread_create(shuffle_threads + i, NULL, &ShuffleThread, wrd_buff_ptrs + i * DIC_WRD_NUM);
            write_err_log("create thread failed"); 
        }
    }
    for (i = 0; i < SHUFFLE_THREAD_NUM; ++i)
    {
        pthread_join(shuffle_threads[i], NULL);
    } 
        /*Sorter Threads */
    for (i = 0; i < SHUFFLE_THREAD_NUM; ++i)
    {
        while (0 != pthread_create(sorter_threads + i, NULL, &SorterThread, wrd_buff_ptrs + i * DIC_WRD_NUM))
        {
            write_err_log("create thread failed"); 
            pthread_create(shuffle_threads + i, NULL, &ShuffleThread, wrd_buff_ptrs + i * DIC_WRD_NUM);
        }
    }

    for (i = 0; i < SHUFFLE_THREAD_NUM; ++i)
    {
        pthread_join(sorter_threads[i], NULL);
    }
}
/* ------------------------------------------------------------------------------------------ */
static void MergeDictionary(char *str_list[], size_t size)
{
    char *aux_array = malloc(sizeof(char*) * size); 
    if (NULL == aux_array)
    {
        write_err_log("aux array create failed"); 
        return; 
    }

    Merge(str_list, str_list + 2 * DIC_WRD_NUM, sizeof(char*), DIC_WRD_NUM * 2, DIC_WRD_NUM * 2 , IsBefore, aux_array);
    Merge(str_list + size/2 , str_list + 3*size/4, sizeof(char*), DIC_WRD_NUM * 2, DIC_WRD_NUM * 2 , IsBefore, aux_array);
    Merge(str_list, str_list + size/2, sizeof(char*), DIC_WRD_NUM * 4, DIC_WRD_NUM * 4 , IsBefore, aux_array);
} 
/* ------------------------------------------------------------------------------------------ */
static void Merge(void *arrA, void *arrB, size_t size, size_t nmembA, size_t nmembB, 
                    int(*cmp)(const void*, const void*), void *arrAux)
{
    char *runnerA = arrA; 
    char *runnerB = arrB; 
    void *headAux = arrAux;
    
    size_t i = 0;
    size_t j = 0; 

    while (i < nmembA && j < nmembB)
    {
        if (cmp(runnerA, runnerB))
        {
            memcpy(arrAux, runnerB, size); 
            runnerB = (char*)((size_t)runnerB + size); 
            ++j; 
        }
        else 
        {
            memcpy(arrAux, runnerA, size);
            runnerA = (char*)((size_t)runnerA + size);  
            ++i;
        } 

        arrAux = (char*)((size_t)arrAux + size);
    }

    while (i < nmembA)
    {
        memcpy(arrAux, runnerA, size);
        runnerA = (char*)((size_t)runnerA + size);
        arrAux = (char*)((size_t)arrAux + size);  
        ++i; 
    }

     while (j < nmembB)
    {
        memcpy(arrAux, runnerB, size);
        runnerB = (char*)((size_t)runnerB + size);
        arrAux = (char*)((size_t)arrAux + size);  
        ++j;
    }

    memcpy(arrA, headAux, nmembA * size);
    headAux = (char*)headAux +  nmembA * size;
    memcpy(arrB, headAux, nmembB * size);
}
/* ----------------------------------------------------- */
static void write_err_log(const char *err)
{
    FILE *fp = fopen("mylog.txt", "a"); 
    fputs (err , fp); 
    fclose(fp);
}