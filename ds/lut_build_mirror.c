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

static unsigned char BitMirror(unsigned char number)
{
    unsigned char p1 = 0, p2 = 0, p3 = 0, p4 = 0, p_all = 0; /*p for pair */
 
    p1 = (number & 1) ^ ((number >> 7) & 1);
    p2 = ((number >> 1) & 1) ^ ((number >> 6) & 1);
    p3 = ((number >> 2) & 1) ^ ((number >> 5) & 1);
    p4 = ((number >> 3) & 1) ^ ((number >> 5) & 1);

    p_all = (((p1 << 7) | (   p1  ))  |
             ((p2 << 6) | (p2 << 1))  |
             ((p3 << 5) | (p3 << 2))  |
             ((p4 << 4) | (p4 << 3)))   ; 
    
    return (number ^ p_all);
}


int main(void)
{
    FILE *f_ptr = NULL; 
    int i = 0;   
    unsigned char chr = 0; 
    f_ptr = fopen("bits_array_lut_mirror.c","w");
    
    if (NULL == f_ptr)
    {
        return(EXIT_FAILURE);
    } 

    fprintf(f_ptr, "unsigned char mirror_lut[%d] = {" ,LUTSIZE);    
    for(i = 0; i < LUTSIZE - 1; ++i)
    {       
        if(i % 4 == 0)
        {
            fputs("\n", f_ptr); 
        }    
        chr = BitMirror(i);
        if(EOF == fprintf(f_ptr, " 0x%x,", chr))
        {
           fputs("ERROR WRITING LUT", stderr); 
            return EXIT_FAILURE; 
        }
    } 
    fprintf(f_ptr, "0x%x};",BitMirror(i));
    if (0 != fclose(f_ptr))
    {
        fputs("ERROR CLOSING FILE", stderr); 
        return EXIT_FAILURE;  
    } 
  
    return (EXIT_SUCCESS);

} 


