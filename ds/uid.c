/*******************************************************************************
* Programmer: Avihay Asraf
* uid.c
* File: uid code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#include "uid.h"

static size_t GetCounter(void);

uid_type UIDCreate(void)
{
    uid_type id = {0};
    id.counter = GetCounter(); 
    id.pid = getpid();
    gettimeofday((&id.time), NULL);
 
    return id; 
}

static size_t GetCounter(void)
{
    static size_t counter = 0; 
    ++counter; 
    
    return counter;  
}

int UIDIsSame(uid_type uid1, uid_type uid2)
{ 
   return (uid1.counter == uid2.counter); 
}

int UIDIsBad(uid_type uid)
{
    return (uid.counter == ~0x0ul);
}

uid_type UIDGetBadUID(void)
{
    uid_type badid = UIDCreate(); 
    badid.counter = ~0x0ul; 
    
    return (badid);
}


