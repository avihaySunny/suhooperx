/*******************************************************************************
* Programmer: Avihay
* sorting.h
* File: sorting header
* Date: ב' יונ 10 11:47:17 IDT 2019
*******************************************************************************/

#ifndef __SORTING_H__
#define __SORTING_H__

void BubbleSort(int *arr, size_t arr_size);

void SelectionSort(int *arr, size_t arr_size);

void CountingSort(int *arr, size_t arr_size);

void InsertionSort(int *arr, size_t size);

void RadixSort(int *arr, size_t size);

void MergeSort(void *base, size_t nmemb, size_t size, int(*cmp)(const void*, const void*));

void QSort(void *base, size_t num_el, size_t el_size, int (*is_before)(const void *, const void*));

void *BinarySearch(void *base, size_t n_elements, size_t el_size, void *data, int (*cmp)(const void*, const void*));

void *BinarySearchIter(void *base, size_t n_elements, size_t el_size, void *data, int (*cmp)(const void*, const void*));

#endif          /* sorting  */







