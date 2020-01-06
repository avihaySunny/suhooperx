/****************************************************************************/
/*                                      WS9_mem.h                           */
/*                                   Avihay Asraf                           */
/*                                    April 2019                            */
/****************************************************************************/
#ifndef __WS9__mem_c__ 
#define __WS9__mem_c__
void *Memset(void *dest, int c, size_t n);                      /* Set in c for n bytes from dest returns dest    */ 
void *Memcpy(void *dest, const void *src, size_t n);            /* copys n bytes from src to des returns dest     */
void *Memmove(void *dest, const void *src, size_t n);           /* moves from src to dest n bytes that may overlap*/    
void MemcpyBackwards(void *dest, const void *src, size_t n);    /* case   src_head < dest_head < src_end          */

#endif 

