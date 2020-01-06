/*******************************************************************************
* Programmer: Avihay Asraf
* knight_tour.c
* File: knight_tour code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#include "heap_sort.h"
#include "knight_tour.h"

#define N_MOVES (8)
typedef struct NumberOfMoves
{
    size_t count; 
    size_t indx;  
}moves_t; 

static int MOV_X[] = {2, 1, -1, -2, -2, -1, 1, 2};
static int MOV_Y[] = {1, 2, 2, 1, -1, -2, -2, -1};

/* -------------------------------------------------------------------------------- */
static int CmpCount(const void *dataA, const void *dataB);
static int CmpCountMove(const moves_t *movA, const moves_t *movB);
static size_t GetNumOfMoves(bits_arr_t *curr_map ,int x, int y);
static void GetBestMoveList(bits_arr_t *curr_map, moves_t *best_moves, int x, int y);
static size_t CordToInx(int x, int y);
static int IsLegitMove(bits_arr_t *current_map, int x, int y); 

/* -------------------------------------------------------------------------------- */
static size_t CordToInx(int x, int y)
{
    return (x + y * 8);
}

int IsLegitMove(bits_arr_t *current_map, int x, int y)
{
    if (0 > x || x >= N || 0 > y || y >= N || BitsArrIsOn(current_map, CordToInx(x,y))) 
    {
        return 0; 
    }

    return 1; 
}

int KnightTour(bits_arr_t *move_map, int x, int y, int *move_list, size_t move_list_indx)
{
    int nxt_x = 0;
    int nxt_y = 0;
    size_t i = 0; 
    moves_t best_move[N] = {0}; 
    
    assert(move_map);
    assert(move_list);

    move_list[move_list_indx] = CordToInx(x,y);
    ++move_list_indx;
    BitsArrSetOn(move_map, CordToInx(x, y));
    
    if (BitsArrCountOn(move_map) == N*N)
    {
        return 1;
    }

    GetBestMoveList(move_map ,best_move, x, y); 
    for (i = 0; i < N; ++i)
    {
        nxt_x = x + MOV_X[best_move[i].indx]; 
        nxt_y = y + MOV_Y[best_move[i].indx];

        if(IsLegitMove(move_map, nxt_x, nxt_y))
        {
            if (KnightTour(move_map, nxt_x, nxt_y, move_list, move_list_indx))
            {
                return 1; 
            }  
        }
    } 

    BitsArrSetOff(move_map, CordToInx(x,y)); 

    return 0; 
}

int IsValidRoute(int *moves_arr, size_t size)
{
    int i = 0; 
    
    assert(moves_arr); 
    BubbleSort(moves_arr, size);
    
    for (i = 0; i < N * N; ++i)
    {
        if (moves_arr[i] != i)
        {
            return 0; 
        }
    }

    return 1; 
}

void PrintRoute(int *moves_arr, size_t size)
{
    size_t i = 0; 
    puts("start ");
    for (i = 0; i < size; ++i)
    {
        printf("-> %d", moves_arr[i]);
        if (i % N == 0 && i != 0)
        {
            puts("");
        }
    }
}

static size_t GetNumOfMoves(bits_arr_t *curr_map ,int x, int y)
{
    size_t count = 0; 
    size_t i = 0;
    int nxt_x = 0; 
    int nxt_y = 0; 

    for (i = 0; i < N; ++i)
    {
        nxt_x = x + MOV_X[i];
        nxt_y = y + MOV_Y[i];
        
        if (IsLegitMove(curr_map, nxt_x, nxt_y))
        {
            ++count; 
        }  
    }

    return count; 
}

static void GetBestMoveList(bits_arr_t *curr_map, moves_t *best_moves, int x, int y)
{
    int next_x = 0; 
    int next_y = 0; 
    size_t i = 0; 
    
    for (i = 0; i < N; ++i)
    {
        next_x = x + MOV_X[i]; 
        next_y = y + MOV_Y[i]; 
        best_moves[i].count = GetNumOfMoves(curr_map ,next_x, next_y);
        best_moves[i].indx = i; 
    }

    HeapSort(best_moves, N, sizeof(moves_t), CmpCount);
}

static int CmpCount(const void *dataA, const void *dataB)
{
    return CmpCountMove(dataA, dataB);
}

static int CmpCountMove(const moves_t *movA, const moves_t *movB)
{
    return movA->count > movB->count; 
} 

#if 0 
        /* scrap of old function */
 /*  for (i = 0; i < N_MOVES; ++i)
    {
        nxt_x = x + MOV_X[i];
        nxt_y = y + MOV_Y[i];
        
        if(IsLegitMove(move_map, nxt_x, nxt_y))
        {
            if (KnightTour(move_map, nxt_x, nxt_y, move_list, move_list_indx))
            {
                return 1; 
            }  
        }
    } */
#endif 