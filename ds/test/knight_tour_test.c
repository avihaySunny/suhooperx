/*******************************************************************************
* Programmer: Avihay Asraf
* knight_tour_test.c
* File: knight_tour testing
* Date: ג' יול  2 08:34:09 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include <time.h>
#include <sys/time.h>       /* timeval                                  */  

#include "knight_tour.h"
#include "sorting.h" 

static float RealTimeDiff(struct timeval *a, struct timeval *b); /*Calcs differencs of two times */ 
static void TestKnightTour(char print_flag);

/* -------------------------------------------------------------------------------- */
int main(void)
{
    struct timeval start = {0}; 
    struct timeval end   = {0};
    char print_flag = 0; 

    puts ("If you wish to print moves press 'p'\n");
    scanf("%c", &print_flag);

    gettimeofday(&start, NULL);
    TestKnightTour(print_flag);
    gettimeofday(&end, NULL);
    printf("time : %1.5f\n", RealTimeDiff(&start, &end));

    return (EXIT_SUCCESS);
}
/* -------------------------------------------------------------------------------- */
static void TestKnightTour(char print_flag)
{
    bits_arr_t board = 0x0UL; 
    int i = 0, j = 0, curr_res; 
    int move_list[N *N ]= {0}; 
    
    for (i = 0; i < N; ++i)
    {
        for (j = 0; j < N; ++j)
        {
            curr_res = KnightTour(&board, i, j, move_list, 0);
            if (curr_res == 0)
            {
                printf("for x : %d y : %d Knight Tour Failed!\n", i, j); 
            }

            if(print_flag == 'p')
            {    
                PrintRoute(move_list, N*N);
                puts("\n------------------------");
            }
            
            if (!IsValidRoute(move_list, N*N))
            {
                puts("Not Valid");
            }
            
            board = 0; 
        }
    }
}
/* -------------------------------------------------------------------------------- */
static float RealTimeDiff(struct timeval *a, struct timeval *b) /*returns seconds*/
{
    assert(a && b);
    return (((b->tv_sec*1e6 + b->tv_usec) - (a->tv_sec *1e6 + a->tv_usec)) / 1000000);
}




