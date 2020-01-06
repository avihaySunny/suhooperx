/****************************************************************************/
/*                                    BitsArray.c                           */
/*                                   Avihay Asraf                           */
/*                                    May 2019                              */
/*                                  Data Structurs                          */  
/****************************************************************************/
#include <assert.h>             /* assert         */
#include <stdio.h>              /*fputs printf .. */ 
#include <stddef.h>             /* size_t         */

#include "./include/bits_array.h"
#define ISALLON
#define WORDSIZE (sizeof(bits_arr_t))
#define BITWORDSIZE (WORDSIZE * 8)

/***********************FUNCTIONS****************************************/
void BitsArrAllOn(bits_arr_t *ba)
{
    assert(ba);
    *ba = ~0;
}

void BitsArrAllOff(bits_arr_t *ba) 
{
    assert(ba);
    *ba = 0;
}

void BitsArrSetOn(bits_arr_t *ba, size_t index)
{
    assert(ba);
    if (index > BITWORDSIZE) 
    {
        fputs ("Invalid input", stderr);
        return; 
    }
    
    *ba |= (1ul << index);         
}

void BitsArrSetBit(bits_arr_t *ba, size_t index, int value)            
{  
    assert(ba);
    if (index > BITWORDSIZE) 
    {
        fputs ("Invalid input", stderr);
        return; 
    }
    
    *ba ^= (-(unsigned long)value ^ *ba) & (1UL << index);
}

void BitsArrSetOff(bits_arr_t *ba, size_t index)           
{
    assert(ba);
    if (index > BITWORDSIZE) 
    {
        fputs ("Invalid input", stderr);
    }
    
    *ba &= ~ (1ul << index); 
}

int BitsArrIsOn(const bits_arr_t *ba, size_t index)       
{
    assert(ba);
    if (index > BITWORDSIZE) 
    {
        fputs ("Invalid input", stderr);
        return 0; 
    }
    return ((*ba >> index) & 1);
}

int BitsArrIsOff(const bits_arr_t *ba, size_t index)      
{
    assert(ba);
    if (index > BITWORDSIZE) 
    {
        fputs ("Invalid input", stderr);
        return 0; 
    }
    
    return (((*ba >> index) & 1) == 0);
}

void BitsArrFlip(bits_arr_t *ba, size_t index)                  
{
    assert(ba);
    if (index > BITWORDSIZE) 
    {
        fputs ("Invalid input", stderr);
        return; 
    }
    
    *ba ^= (1ul << index);
} 

void BitsArrFlipAll(bits_arr_t *ba)                  
{
    assert(ba);
    *ba = ~*ba; 
} 

void BitsArrRotateRight(bits_arr_t *ba, size_t turns)      
{ 
    assert(ba);
  
    turns = turns % BITWORDSIZE;
    *ba = (*ba >>turns | (*ba << (BITWORDSIZE - turns)));
}

void BitsArrRotateLeft(bits_arr_t *ba, size_t turns)      
{
    assert(ba);
    
    turns %= BITWORDSIZE;
    if (turns == 0)
    {
        return;
    }
    
    *ba = (*ba >> (BITWORDSIZE - turns) | (*ba << turns));
}

void BitsArrMirror(bits_arr_t *ba)
{
    bits_arr_t mirrored = 0;
    bits_arr_t copy = *ba; 
    size_t i = 0;
    
    assert(ba);
    
    for (; i < BITWORDSIZE; ++i)
    {
        if (copy & 1)
        {
            mirrored <<= 1;
            mirrored += 1;
        }

        else
        {
            mirrored <<= 1;
        }

        copy >>= 1 ;
    }
    
    *ba = mirrored; 
}

int BitsArrCountOn(const bits_arr_t *ba)                          
{
    bits_arr_t x = *ba; 
    assert(ba);
 
    x = (x & 0x5555555555555555 ) + ((x >>  1) & 0x5555555555555555 ); 
    x = (x & 0x3333333333333333 ) + ((x >>  2) & 0x3333333333333333 );  
    x = (x & 0x0f0f0f0f0f0f0f0f ) + ((x >>  4) & 0x0f0f0f0f0f0f0f0f ); 
    x = (x & 0x00ff00ff00ff00ff ) + ((x >>  8) & 0x00ff00ff00ff00ff ); 
    x = (x & 0x0000ffff0000ffff)  + ((x >> 16) & 0x0000ffff0000ffff); 
    if (BITWORDSIZE == 32)
    {
        return (x & 0x3f); 
    }
    
    x = (x & 0x00000000ffffffff) + ((x >> 32) & 0x00000000ffffffff);  
    
    return (int)x; 
}

int BitsArrCountOff(const bits_arr_t *ba)                        
{
    bits_arr_t x = *ba; 
    assert(ba);
    
    x = (x & 0x5555555555555555 ) + ((x >>  1) & 0x5555555555555555 ); 
    x = (x & 0x3333333333333333 ) + ((x >>  2) & 0x3333333333333333 );  
    x = (x & 0x0f0f0f0f0f0f0f0f ) + ((x >>  4) & 0x0f0f0f0f0f0f0f0f ); 
    x = (x & 0x00ff00ff00ff00ff ) + ((x >>  8) & 0x00ff00ff00ff00ff ); 
    x = (x & 0x0000ffff0000ffff)  + ((x >> 16) & 0x0000ffff0000ffff);
    if (BITWORDSIZE == 32)
    {
        return ( BITWORDSIZE - (x & 0x3f)); 
    }
    
    x = (x & 0x00000000ffffffff) + ((x >> 32) & 0x00000000ffffffff);  
    
    return (int)(BITWORDSIZE - x);   
}

void BitsArrSetRangeOn(bits_arr_t *ba, size_t index_start, size_t index_end)
{
    size_t value = 1; 
    assert (ba);
    if ((index_start > BITWORDSIZE ) || (index_end > BITWORDSIZE))
    {
        fputs("Invalid input", stderr);
        return; 
    }
    
    while (index_end > index_start)
    {
        *ba ^= (-value ^ *ba ) & (1ul << index_start);
        ++index_start;
    }
}
void BitsArrSetRangeOff(bits_arr_t *ba, size_t index_start, size_t index_end)
{
    size_t value = 0; 
    assert(ba);
    
    if ((index_start > BITWORDSIZE ) || (index_end > BITWORDSIZE))
    {
        fputs("Invalid input", stderr);
        return; 
    }
    
    while (index_end > index_start)
    {
        *ba ^= (-value ^ *ba ) & (1ul << index_start);
        ++index_start;
    }
}


void BitsArrPrint(const bits_arr_t ba)
{
    int i = BITWORDSIZE - 1;
   
    for (; i >= 0 ; --i)
    {
        ((ba >> i) & 1 ) ?  printf("1"): printf("0"); 
    } 
    
    puts(" ");
}
/* 
int BitArrFastCountOn(const bits_arr_t *ba)
{
    unsigned int i = 0, count = 0; 
    unsigned char *byte_ptr = NULL;
    bits_arr_t temp = 0; 
    extern unsigned char count_ones[]; 
    assert(ba); 
    byte_ptr = (unsigned char*)ba;
    
    for (i = 0, temp = *ba; i < WORDSIZE && 0 != temp; ++i)
    {
        count += count_ones[*byte_ptr];
        ++byte_ptr; 
        temp >>= 8; 
    } 

    return count; 
}
 
void BitArrFastMirror(bits_arr_t *ba)
{
    bits_arr_t temp = 0; 
    unsigned char *byte_ptr = NULL;
    int i = 0; 
    extern unsigned char mirror_lut[];
    
    assert(ba); 
    byte_ptr = (unsigned char*)ba;
    
    for (i = WORDSIZE - 1; i >= 0; --i)
    {
        temp += (bits_arr_t)mirror_lut[*byte_ptr] << (i * 8);
        ++byte_ptr;
    }
        
    *ba = temp;  
}      
  */
       
              


