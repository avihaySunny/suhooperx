/*******************************************************************************
* Programmer: Avihay
* shufflensort.h
* File: shufflensort header
* Date: ה' יול 18 15:27:48 IDT 2019
*******************************************************************************/

#define UPPER_LIMIT (25)
#define DIC_WRD_NUM (102305)
#define NUM_OF_COPIES (8)
#define SHUFFLE_THREAD_NUM (4)
#define SORTER_THREAD_NUM (4)

#ifndef __SHUFFLENSORT_H__
#define __SHUFFLENSORT_H__

void ShuffleAndSort (char *wrd_buff_ptrs[], char *buffer, size_t *count);


#endif          /* shufflensort  */







