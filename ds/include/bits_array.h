/****************************************************************************/
/*                                    BitsArray.h                           */
/*                                   Avihay Asraf                           */
/*                                    May 2019                              */
/*                                  Data Structurs                          */  
/****************************************************************************/
#include <stddef.h>         /* size_t */

#ifndef __BITS_ARRAY_H__
#define __BITS_ARRAY_H__   

typedef unsigned long bits_arr_t;                               /* word size type               */  
    
#define BIT_ARR_BITS_NUM (sizeof(bits_arr_t) * 8)               /* (64 bits)                    */
               
void BitsArrAllOn(bits_arr_t *ba);                              /*Turns all bits on             */

void BitsArrAllOff(bits_arr_t *ba);                             /*Turns all bits off            */
  
void BitsArrSetOn(bits_arr_t *ba, size_t index);                /*Turns bit i on                */
 
void BitsArrSetBit(bits_arr_t *ba, size_t index, int value);    /* set bit i                    */

void BitsArrSetOff(bits_arr_t *ba, size_t index);               /*Turns bit i off               */

int BitsArrIsOn (const bits_arr_t *ba, size_t index);           /*Checks i bit state on         */

int BitsArrIsOff (const bits_arr_t *ba, size_t index);          /*Checks i bit state off        */

void BitsArrFlip (bits_arr_t *ba, size_t index);                /*Flips array bit big not       */

void BitsArrFlipAll (bits_arr_t *ba);                           /*Flips array bit big not       */
 
void BitsArrRotateRight(bits_arr_t *ba, size_t index);          /*Rotates all bit to the right  */

void BitsArrRotateLeft(bits_arr_t *ba, size_t index);           /*Rotates all bit to the left   */

void BitsArrMirror(bits_arr_t *ba);                             /*Mirrors bits array            */

int BitsArrCountOn(const bits_arr_t *ba);                       /*Count # of on Bits            */ 

int BitsArrCountOff(const bits_arr_t *ba);                      /*Count # of off Bits           */

void BitsArrSetRangeOn(bits_arr_t *ba, size_t index_start, size_t index_end);

void BitsArrSetRangeOff(bits_arr_t *ba, size_t index_start, size_t index_end);

void BitArrFastMirror(bits_arr_t *ba); 

int BitArrFastCountOn(const bits_arr_t *ba); 

#ifdef DEBUG /*for print function */ 
void BitsArrPrint(bits_arr_t *ba);                            /*prints number on debug mode   */
#endif /*end for print debug function */

    #endif 

