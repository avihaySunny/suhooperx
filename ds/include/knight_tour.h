/*******************************************************************************
* Programmer: Avihay
* knight_tour.h
* File: knight_tour header
* Date: ג' יול  2 08:34:09 IDT 2019
*******************************************************************************/

#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#include "bits_array.h" 
#include "sorting.h"

#define N (8)

int KnightTour(bits_arr_t *move_map, int x, int y, int *move_list, size_t move_list_indx);
int IsValidRoute(int *moves_arr, size_t size);
void PrintRoute(int *moves_arr, size_t size);

#endif          /* knight_tour  */







