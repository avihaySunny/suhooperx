#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


const size_t num_to_divide = 5754853344;
void *ThreadSumOfDividers(void *range);
void *ThreadAddToArr(void *arg);
size_t sum_of_dividers = 0; 
static void initRanges(void);

typedef struct range 
{
    size_t start; 
    size_t end;  
} range_t;

range_t ranges[4] = {0}; 
                                          
int main (void)
{
    size_t i = 0;
    void *status = NULL; 
    pthread_t my_thread[4] = {0};

    initRanges();

    for (i = 0; i < 4; ++i)
    {  
        pthread_create(&my_thread[i], NULL, &ThreadSumOfDividers, &ranges[i]);
        pthread_detach(my_thread[i]);  
      /*  pthread_join(my_thread[i], &status); */
    }
    
    sleep(15);

    printf("%ld\n", sum_of_dividers);

    return EXIT_SUCCESS;
}

void *ThreadSumOfDividers(void *range)
{
    range_t *new = range; 
    size_t reminder = 0; 
    size_t i = 0; 

    for (i = new->start; i <= new->end; ++i)
    {
        if (0 == (reminder = num_to_divide % i))
        {
            printf("%ld\n", i );
            sum_of_dividers += i;
        }
    }

    return range;
}

static void initRanges(void)
{
    ranges[0]. start = 1; ranges[0]. end = num_to_divide / 4;
    ranges[1]. start = (num_to_divide / 4) + 1; ranges[1]. end = num_to_divide / 2;
    ranges[2]. start = (num_to_divide / 2) + 1; ranges[2]. end = 3 *num_to_divide / 4;
    ranges[3]. start = 3 *(num_to_divide / 4) + 1; ranges[3]. end = num_to_divide ;     
}
