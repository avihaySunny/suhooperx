/****************************************************************************/
/*                                      WS9_mem.c                           */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/
#include <stdio.h>      /*fputs, printf         */
#include <assert.h>     /* assert               */

#include "ws9_mem.h" 

#define WORD_SIZE (sizeof(size_t))
/*************************FUNCTIONS**************************************/
void *Memset(void *dest, int c, size_t n) 
{ 
    size_t *dest_runner = NULL; 
    size_t tail = 0;
    size_t i = 0;  
    unsigned char *sec_runner = NULL; 
    size_t val = 0; 
    size_t word_size = WORD_SIZE; 
    size_t align_diff = (size_t)dest;  
        
    assert (dest);
    dest_runner = (size_t*)dest;
    align_diff = (word_size - (align_diff & (word_size - 1))) & (word_size - 1);    /*  approx means (num - num % 8)   */
    for (i = 0; i < (word_size / sizeof(char)); ++i)
    {
        val <<= word_size;
        val += c;
    }
  
    if (align_diff)                                                                 /*case address not aligned         */
    {
        sec_runner = (unsigned char*)dest_runner; 
        for (i = 0; i < align_diff; ++i, --n)
        {
            *sec_runner = c; 
            ++sec_runner;     
        }
        
        dest_runner = (size_t*)sec_runner; 
    }
    
    for (i = 0; i < (n / word_size); ++i)
    {                                                           
        *dest_runner = val;                                        
        ++dest_runner; 
    }
    
    tail = n & (word_size - 1);        /*  = n % 7 */
    if (tail)
    {
        sec_runner = (unsigned char*)dest_runner;
        for (i = 0; i < tail; ++i)
        {
            *sec_runner = c; 
            ++sec_runner; 
        }
    }   
    
    return dest;    
}

void *Memcpy(void *dest, const void *src, size_t n)    /*n is size in bytes */
{
    size_t *dest_runner = NULL;
    const size_t *src_runner = NULL; 
    size_t tail = 0;
    size_t i = 0; 
    unsigned char *sec_src_rnr = NULL; 
    unsigned char *sec_des_rnr = NULL;
    size_t word_size = WORD_SIZE; 
    size_t align_diff = (size_t)dest;  
    
    assert (dest);  
    assert (src); 
    
    align_diff = (word_size - (align_diff & (word_size - 1))) & (word_size - 1);   
    dest_runner = (size_t*)dest; 
    src_runner = (size_t*)src;  
    if (align_diff)  /*case address not aligned */
    {
        sec_des_rnr = (unsigned char*)dest_runner; 
        sec_src_rnr = (unsigned char*)src_runner; 
        for(i = 0; i < align_diff; ++i)
        {
            *sec_des_rnr = *sec_src_rnr;
            ++sec_des_rnr;
            ++sec_src_rnr; 
            --n; 
        }
        
        dest_runner = (size_t*)sec_des_rnr; 
        src_runner = (size_t*)sec_src_rnr;   
    }
    
    for (i = 0; i < (n / word_size); ++i)
    {
        *dest_runner = *src_runner; 
        ++dest_runner; 
        ++src_runner;   
    }
    
    tail = n & (word_size - 1); /* basically its n % 7 just faster*/
    if(tail)
    {
        sec_des_rnr = (unsigned char*)dest_runner; 
        sec_src_rnr = (unsigned char*)src_runner; 
        for(i = 0; i < tail; ++i)
        {
            *sec_des_rnr = *sec_src_rnr;
            ++sec_des_rnr;
            ++sec_src_rnr; 
        }
    }
    
    return dest;   
}

void *Memmove(void *dest, const void *src, size_t n)
{
    char *src_head = NULL;
    char *src_end = NULL; 
    char *dest_head = NULL; 
    char *dest_end = NULL; 
   
    assert(dest);
    assert(src);
       
    src_head = (char*)src; 
    src_end = src_head + n;  
    dest_head = (char*)dest; 
    dest_end = dest_head + n;       
    
    if (dest_head > src_head)
    {
        MemcpyBackwards(dest_end, src_end, n); 
    }
 
    else 
    {
        Memcpy(dest, src, n);
    } 
    return dest;  
}

void MemcpyBackwards(void *dest, const void *src, size_t n)  /* case   src_head < dest_head < src_end */
{
    size_t *dest_runner = NULL;
    const size_t *src_runner = NULL; 
    size_t tail = 0;
    size_t i = 0;  
    size_t word_size = WORD_SIZE; 
    unsigned char *sec_src_rnr = NULL; 
    unsigned char *sec_des_rnr = NULL;
    
    assert(dest);
    assert(src);
    
    dest_runner = (size_t*)dest - 1; 
    src_runner = (size_t*)src - 1;
    tail = n & (word_size - 1);                             /* basically its n % 7 just faster*/ 
    for (i = 0; i < (n / word_size); ++i)
    {
        *dest_runner = *src_runner; 
        --dest_runner; 
        --src_runner;  
    }
    
    if(tail)
    {
        sec_des_rnr = (unsigned char*)dest - i * word_size; 
        sec_src_rnr = (unsigned char*)src - i * word_size; 
        for(i = 0; i <= tail; ++i)
        {
            *sec_des_rnr = *sec_src_rnr;
            --sec_des_rnr;
            --sec_src_rnr;           
        }    
    }     
}

