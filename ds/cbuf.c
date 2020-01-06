/*******************************************************************************
* Programmer: Avihay Asraf
* cbuf.c
* File: cbuf code
* Date: א' מאי 12 17:47:49 IDT 2019
*******************************************************************************/


#include <stdio.h>          /* printf   */
#include <stdlib.h>         /* malloc   */
#include <string.h>         /* memcpy   */
#include <assert.h>         /* assert   */
#include <errno.h>          /* perror   */
#include "./include/cbuf.h"

#define ABS(var) ((var < 0)? (var = -var): (var))

struct c_buffer
{
    char *end;              /*keeps the position of last element in queue*/
    char *reader;
    char *writer;
    char data[1];           /*keeps the start of allocated mem for data*/
};

cbuf_t *CBufCreate(size_t nbytes)
{
    cbuf_t *cb = (cbuf_t*)malloc(sizeof(cbuf_t) + nbytes ); /*extra one for delta to know the difference*/

    if ((NULL == cb) || (0 == nbytes))
    {
        return (NULL);
    }

    cb->end    = cb->data + nbytes ;
    cb->reader = cb->data;
    cb->writer = cb->data;

    return (cb);
}

void CBufDestroy(cbuf_t *cb)
{
    if(cb == NULL)
    {
        return;
    }

    cb->end    = NULL;
    cb->reader = NULL;
    cb->writer = NULL;
    
    free(cb);
    cb = NULL;
}

size_t CBufGetCapacity(const cbuf_t *cb)
{
    assert(cb);

    return (cb->end - cb->data);
}

size_t CBufGetFreeSpace(const cbuf_t *cb)
{
    assert(cb);
    
    if ((cb->writer == cb->data) && (cb->reader == cb->data))
    {
        return (CBufGetCapacity(cb));
    }
    
    if (cb->writer == cb->reader + 1) /*is empty*/
    {
        return (CBufGetCapacity(cb));
    
    }
    if (cb->reader == cb->writer + 1)  /*is full*/
    {
        return (0);
    
    }
    if ((cb->writer == cb->end) && (cb->reader == cb->data))
    {
       
        return (0);
    }
    
    if (cb->writer > cb->reader)      /*  S R W E */
    {
     
        return (CBufGetCapacity(cb) - (cb->writer - cb->reader));
    }
   
    return (cb->reader - cb->writer - 1); /*  S W R E */
}

int CBufIsEmpty(const cbuf_t *cb)
{
    assert(cb);
    
    return (CBufGetCapacity(cb)  == CBufGetFreeSpace(cb));
}

ssize_t CBufWrite(cbuf_t *cb, const void *src, size_t nbytes)
{
    size_t overhead = 0;
    size_t available = 0;
    unsigned char overhead_b = 0; 
    errno = 0;
    
    assert(cb);
    assert(src);

    overhead = cb->end - cb->writer;
    available = CBufGetFreeSpace(cb);
    
    if (0 == available)
    {
        return (-1);
    }

    if (nbytes > available)
    {
        nbytes = available;
       /* errno = EOVERFLOW;*/
    }
    
    if(nbytes > overhead)
    {  
        memcpy(cb->writer, src, overhead); 
        cb->writer = cb->data; 
        nbytes -=overhead; 
        overhead_b = 1;
    }
    
    memcpy(cb->writer, src, nbytes );       /*default operation */
    cb->writer = cb->writer + nbytes; 

    if ((cb->writer == cb->reader + 1) && (available == nbytes ))
    {
        cb->reader = cb->reader + 2;
    }
    
    return (nbytes + overhead * overhead_b);    
}

ssize_t CBufRead(cbuf_t *cb,void *dest, size_t nbytes)
{
    size_t overhead = 0;
    size_t available = 0;
    unsigned char overhead_b = 0; 
    errno = 0;
    
    assert(cb);
    assert(dest);
    
    if (CBufIsEmpty(cb))
    {
        
        /*errno = ENDODATA;*/
        return (-1);
    }
    
    overhead = cb->end - cb->reader;                        
    available = CBufGetCapacity(cb) - CBufGetFreeSpace(cb); /*available to read*/
    
    if(nbytes > available)
    {
        nbytes = available - 1; 
    }
    
    if(nbytes > overhead)
    {
        memcpy(dest, cb->reader, nbytes);
        cb->writer = cb->data; 
        nbytes -= overhead;
        overhead_b = 1;
        dest = (char*)dest + nbytes; 
    }
    
    memcpy(dest, cb->reader, nbytes);       /*default operation */
    cb->reader = cb->reader + nbytes; 
    
    if (cb->reader == cb->writer)
    {
        --cb->reader;
    }  
    return (nbytes + overhead * overhead_b) ;
}

#ifndef DNDEBUG

void CBufPrint(const cbuf_t *cb, size_t nbytes)
{
    const char *runner = NULL; 
    size_t i        = 0; 
    size_t available = 0;
    size_t overhead  = 0;  
    assert(cb); 
   
    runner = cb->reader; 
    if(CBufIsEmpty(cb))
    {   
        puts("Buffer is empty\n");
    }
    
    available = CBufGetCapacity(cb) - CBufGetFreeSpace(cb);
    overhead = cb->end - cb->reader; 
    
    puts(CYAN"Prints MetaData:"RESET); 
    printf("Buffer Capacity %ld\n", CBufGetCapacity(cb)); 
    printf("Available space %ld\n", CBufGetFreeSpace(cb)); 

    if (nbytes > available)             /*shortens if not enough to read*/
    {
        nbytes = available - 1; 
    } 
    
    if (nbytes > overhead)     
    {
        for (i = 0; i < overhead; ++i, ++runner)
        {
            printf("%c",*runner);
        }
        
        nbytes -= overhead; 
        runner = cb->data; 
    }
    
    for (i = 0; i < nbytes; ++i, ++runner)
        {
            printf("%c\n",*runner);
        }
}
#endif /*debug*/




