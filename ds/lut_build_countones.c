/****************************************************************************/
/*                                  BitsArrayTests.c                      */
/*                                   Avihay Asraf                           */
/*                                    May 2019                              */
/*                                  Data Structurs                          */  
/****************************************************************************/

#include <stdio.h> 
#include <stdlib.h> 

#define BIT_ARR_BITS_NUM (sizeof(bits_arr_t) * 8)   
#define LUTSIZE (256)

static int CountOnBits(unsigned int x)
{
    int count = 0;

    while(0 != x )
    {
        count +=  x & 1;
        x >>= 1;
    }

    return count;
}

int main(void)
{
    FILE *f_ptr = NULL; 
    int i = 0;
    int count = 0;    
    f_ptr = fopen("bits_array_lut_count.c","w");
    
    if (NULL == f_ptr)
    {
        return(EXIT_FAILURE);
    } 

    fprintf(f_ptr, "unsigned char count_ones[%d] = {",LUTSIZE);    
    for(i = 0; i < LUTSIZE - 1; ++i)
    {        
        if(i % 4 == 0)
        {
            fputs("\n", f_ptr); 
        } 
        count = CountOnBits(i);
        if(EOF == fprintf(f_ptr, "%d, ",count))
        {
           fputs("ERROR WRITING LUT", stderr); 
            return EXIT_FAILURE; 
        }
    } 
   
    fprintf(f_ptr, " %d};", CountOnBits(i));
    if (0 != fclose(f_ptr))
    {
        fputs("ERROR CLOSING FILE", stderr); 
        return EXIT_FAILURE;  
    } 
  
    return (EXIT_SUCCESS);
} 


