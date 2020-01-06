/*******************************************************************************
* Programmer: Avihay
* cbuf.h
* File: cbuf header
* Date: א' מאי 12 17:47:49 IDT 2019
*******************************************************************************/

#ifndef __CBUF_H__
#define __CBUF_H__

#include <sys/types.h>                 /*For ssize_t usage */

        /*Color Scheme*/
#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

        /*Debug define */
#ifndef  NDEBUG 
#define DBG(x)  x 
#else 
#define DBG(x) 
#endif

typedef struct c_buffer cbuf_t; 

cbuf_t *CBufCreate(size_t capacity);

void CBufDestroy(cbuf_t *cb);

ssize_t CBufWrite(cbuf_t *cb, const void *src, size_t nbytes);

ssize_t CBufRead(cbuf_t *cb,void *dest, size_t nbytes);

int CBufIsEmpty(const cbuf_t *cb);

size_t CBufGetCapacity(const cbuf_t *cb); 

size_t CBufGetFreeSpace(const cbuf_t *cb);

#ifndef DNDEBUG

void CBufPrint(const cbuf_t *cb, size_t nbytes);

#endif  /* debug mode*/

#endif  /*cbuf.h*/





