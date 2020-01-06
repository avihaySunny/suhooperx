/*******************************************************************************
* Programmer: Avihay Asraf
* sorting.c
* File: sorting code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <sys/types.h>      /* ssize_t                                  */
#include <string.h>
#include "sorting.h"
/*-------------------------------------------------------------------------*/
#define BASE (10)
#define RANGE (100)
#define MAX(a, b) ((a > b) ? (a) : (b))
#define Q_SIZE (50000)
/*--------------------------------------------------------------------------*/
static void Swap(int *a, int *b); 
static int RadixMax(int *arr, size_t size);
static void Merge(void *arrA, void *arrB, size_t size, size_t nmembA, size_t nmembB, int(*cmp)(const void*, const void*), void *arrAux);
static void MergeSorter(void *start, size_t n_element, size_t element_size, int(*cmp)(const void*, const void*), void *auxArr);
static void QSortRec(void *base, size_t start, size_t end, size_t el_size, int (*is_before)(const void *, const void*));
static size_t QSortPartition(void *base, size_t start, size_t end, size_t el_size, int (*is_before)(const void *, const void*));
static void SwapComData(void *ptrA, void *ptrB, size_t el_size);
static void *GetItemData(void *base, size_t indx, size_t el_size);
static void *BSearchRec(void *base, size_t start, size_t end, size_t el_size, void *data, int (*cmp)(const void*, const void*));
/*--------------------------------------------------------------------------*/
void BubbleSort(int *arr, size_t arr_size)
{

    size_t i = 0, j = 0;

    assert(arr);

    for (i = 0; i < arr_size; ++i)
    {
        for (j = 0; j < arr_size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                Swap(&arr[j], &arr[j + 1]);
            }
        }
    }

}
void SelectionSort(int *arr, size_t arr_size)
{
    int min = arr[0];
    size_t i = 0, j = 0;

    assert(arr);
    
    for (i = 0; i < arr_size; ++i)
    {
        for (j = i; j < arr_size; ++j)
        {
            if (arr[j] < min)
            {
                Swap(&arr[j], &min);
            }
        }

        Swap(&arr[i], &min);
    }
}

void InsertionSort(int *arr, size_t size)
{
    size_t i = 0;
    int current =0, j = 0;

    assert(arr);
    
    for ( i = 1; i < size; ++i)
    {
        current = arr[i]; 
        j = i - 1;
        while (j >= 0 && arr[j] > current)
        { 
            arr[j + 1] = arr[j]; 
            --j; 
        }
        arr[j + 1] = current; 
    }
}

void CountingSort(int *arr, size_t arr_size)
{
    size_t i = 0, j = 0;
    int histogram[Q_SIZE] = {0};

    assert(arr);

    for (i = 0; i < arr_size; ++i)
    {
        ++histogram[arr[i]];
    }

    i = 0;

    for (i = 0; i < RANGE; ++i)
    {
        while (0 < histogram[i])
        {
            arr[j] = i; 
            ++j;
            --histogram[i];
        }
    }
}

void RadixSort(int *arr, size_t size)
{
    int bucket[BASE] = {0};
    int *semi_sorted = NULL;
    int sig_digit = 1;
    int max_element = 0; 
    ssize_t i = 0;
    
    assert(arr);
    
    max_element = RadixMax(arr, size);
    semi_sorted = (int *)calloc(size, sizeof(int));
    
    while ((max_element / sig_digit) > 0 )
    {
        for (i = 0; (size_t)i < size; ++i)
        {
            ++bucket[(arr[i] / sig_digit) % BASE];
        }

        for (i = 1; i < BASE; ++i)
        {
            bucket[i] += bucket[i - 1];
        }
        
        for (i = size - 1; i >= 0; --i)
        {
            semi_sorted[--bucket[(arr[i] / sig_digit) % BASE]] = arr[i];
        }

        memset(bucket, 0, BASE * sizeof(int));
        memcpy(arr, semi_sorted, size * sizeof(int));
    
        sig_digit *= BASE;
    }

    free(semi_sorted);
    semi_sorted = NULL;
}


static void Swap(int *a, int *b)
{
    int temp = *a;
    
    assert(a && b);

    *a = *b;
    *b = temp;
}

static int RadixMax(int *arr, size_t size)
{
    size_t i = 0;
    int max = 0;  
    
    assert(arr);
    
    for (i = 0; i < size; ++i)
    {
        max = MAX(arr[i], max);
    }
    
    return max; 
}

 void MergeSort(void *base, size_t nmemb, size_t size, int(*cmp)(const void *dataA, const void *dataB))
 {
     void *auxArr = malloc(size * nmemb); 
     if (!auxArr)
     {
         return;
     }

     MergeSorter(base, nmemb, size, cmp, auxArr);
     
     free(auxArr);
 }


static void MergeSorter(void *start, size_t n_element, size_t element_size, int(*cmp)(const void*, const void*), void *auxArr)
{
    size_t size_left  = n_element / 2; 
    size_t size_right = n_element / 2 + n_element % 2  - (1 == n_element); 
 
    void *left = start; 
    void *mid = (char*)start + element_size * size_left; 

    if(0 == n_element)
    {
        return; 
    }

    MergeSorter(left, size_left, element_size, cmp, auxArr); 
    MergeSorter(mid , size_right , element_size, cmp, auxArr);

    Merge(left, mid, element_size, size_left, size_right, cmp, auxArr);
    
}  

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

void QSort(void *base, size_t num_el, size_t el_size, int (*is_before)(const void *, const void*))
{
    assert(base);
    
    QSortRec(base, 0, num_el -1, el_size, is_before);
} 

static void QSortRec(void *base, size_t start, size_t end, size_t el_size, int (*is_before)(const void *, const void*))
{
    size_t p_indx = start; 
    assert(base);

    if (start < end)
    {
        p_indx = QSortPartition(base, start, end, el_size, is_before);
       
        QSortRec(base, start, p_indx - 1  ,el_size, is_before);
        QSortRec(base, p_indx + 1 , end ,el_size, is_before);  
    }    
}
static size_t QSortPartition(void *base, size_t start, size_t end, size_t el_size, int (*is_before)(const void *, const void*))
{
    size_t pivot_indx = end ; 
    size_t p_indx = start; 
    size_t i = 0;
     
    assert(base);

    for (i = start; i < end ; ++i)
    {
        if (is_before(GetItemData(base, pivot_indx, el_size),GetItemData(base, i, el_size)))
        {
            SwapComData(GetItemData(base, p_indx, el_size),GetItemData(base, i, el_size), el_size);
            ++p_indx;
        }
    }
    
    SwapComData(GetItemData(base, pivot_indx, el_size), GetItemData(base, p_indx, el_size), el_size);
    if (p_indx == 0)
    {
        p_indx = end; 
    }

    return p_indx; 
}

static void *GetItemData(void *base, size_t indx, size_t el_size)
{
    return (void*)((size_t)base + indx * el_size);
}

static void SwapComData(void *ptrA, void *ptrB, size_t el_size)
{
    void *tmp = malloc(el_size); 
    if (ptrA != ptrB)
    {
        memcpy(tmp, ptrA, el_size);
        memcpy(ptrA, ptrB, el_size); 
        memcpy(ptrB, tmp, el_size); 
    }

    free(tmp);
}

void *BinarySearch(void *base, size_t n_elements, size_t el_size, void *data, int (*cmp)(const void*, const void*))
{
    size_t start = 0; 
    size_t end = n_elements; 
    
    assert(base); 

    return (BSearchRec(base, start, end , el_size, data, cmp));
}

static void *BSearchRec(void *base, size_t start, size_t end, size_t el_size, void *data, int (*cmp)(const void*, const void*))
{
    size_t mid = (start + end) / 2; 
    int cmp_result = 0; 
    
    if (start > end)
    {
        return NULL; 
    }
    
    cmp_result = cmp(GetItemData(base, mid, el_size), data);
    if (0 == cmp_result)
    {
        return GetItemData(base, mid, el_size); 
    } 
    return ((cmp_result > 0) ?  (BSearchRec(base, start, mid - 1, el_size, data, cmp )): 
                                 BSearchRec(base, mid +1, end, el_size, data, cmp    )); 
}

void *BinarySearchIter(void *base, size_t n_elements, size_t el_size, void *data, int (*cmp)(const void*, const void*))
{
    size_t start = 0; 
    size_t end = n_elements; 
    size_t mid = (start + end) / 2 ;
    int cmp_res = 0; 

    assert(base); 

    while (start <= end)
    {  
        cmp_res = cmp(GetItemData(base, mid, el_size), data);
        if (0 == cmp_res)
        {
            return GetItemData(base, mid, el_size);
        }
        else if (cmp_res > 0)
        {
            end = mid - 1; 
        }
        else
        {
            start = mid + 1; 
        }   

        mid = (start + end) / 2; 
    }

    return NULL;
}
