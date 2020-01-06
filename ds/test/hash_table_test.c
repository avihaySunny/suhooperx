/*******************************************************************************
* Programmer: Avihay Asraf
* hash_table_test.c
* File: hash_table testing
* Date: א' יונ 23 11:57:12 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <ctype.h>          /*to lower                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include <strings.h>        /* strcasecmp                                */
#include "hash_table.h"

#define DICT_SIZE (99154) 
#define UPPER_LIMIT (50)
#define UNUSED(a)   ((void)(a))
#define LETTERS (26)

/* ------------------------------------------------------------------------ */
char *strdup(const char *s);
static size_t DataToIndex(void *data); 
static size_t CharToData(char *str); 
static int IsMatch(const void *dataA, const void *dataB);
static void DictionaryHashLoader(hash_t *hash, void *ptr_arr[]);
static void DestroyWords(void **ptr_arr);
static void DictionaryEventLoop(const hash_t *hash);
/*------------------------------------------------------------------------- */
int main(void)
{
    hash_t *hash = HASHCreate(DataToIndex, LETTERS, IsMatch);
    static void *wrd_list_ptr[DICT_SIZE] = {NULL};
    DictionaryHashLoader(hash, wrd_list_ptr); 
    DictionaryEventLoop(hash); 
    HASHDestroy(hash); 
    DestroyWords(wrd_list_ptr);
   
    return (EXIT_SUCCESS);
}

static size_t DataToIndex(void *data)
{
    return(CharToData(data));
}

static size_t CharToData(char *str)
{
    return (tolower(*str) - 'a');
}

static int IsMatch(const void *dataA, const void *dataB)
{
    assert(dataA && dataB);

    return (0 == strcasecmp(dataA, dataB));
}

static void DictionaryHashLoader(hash_t *hash, void *ptr_arr[])
{
    FILE *dictionary = NULL;  
    char word_buff[UPPER_LIMIT] = {0}; 
    size_t i = 0; 

    assert(hash); 

    dictionary = fopen("/usr/share/dict/american-english", "r");
    if (NULL == dictionary)
    {
        return;
    }

    while (NULL != fgets(word_buff, UPPER_LIMIT, dictionary))
    {
        ptr_arr[i] = strdup(word_buff);
        HASHInsert(hash, ptr_arr[i]);
        ++i; 
    }

    fclose(dictionary);
}

static void DestroyWords(void *ptr_arr[])
{
    size_t i = 0; 
    for (i = 0; i < DICT_SIZE; ++i)
    {
        free(ptr_arr[i]);
    }
}

static void FindWord(const hash_t *hash, const char *word)
{
    char *found = NULL; 
    
    assert(hash); 
    assert(word);

    found = HASHFind(hash, word);
    if (NULL == found)
    {
        puts ("Word Does Not exist / Incorrect spelling \n");
    }
    else 
        puts ("Words Exists\n");
}

static void DictionaryEventLoop(const hash_t *hash)
{
    char word_buff[50] = {0};
    int status = 0; 
    puts ("Enter word to look up in dictionary, or enter 'exit' to exit"); 
    status = scanf("%s", word_buff);
    while (0 != strcmp(word_buff, "exit") && status != 0)
    {
        word_buff[strlen(word_buff)] = '\n';  
        FindWord(hash, (const char *)word_buff);
        memset(word_buff, 0, 50);
        status = scanf("%s", word_buff);
    }

}
