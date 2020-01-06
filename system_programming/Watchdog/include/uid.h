/*******************************************************************************
* Programmer: Avihay
* uid.h
* File: uid header
* Date: ד' מאי 22 17:59:43 IDT 2019
*******************************************************************************/

#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>

#ifndef __UID_H__
#define __UID_H__

typedef struct uid
{
    pid_t  pid; 
    struct timeval time; 
    size_t counter;  
    
} uid_type; 

/*Creates a valid UID and returns it to user
* UID IS INVALID If counter is ~0x0ul; 
*/
uid_type UIDCreate(void);  

/*Returns 1 for identical UIDS, 0 otherwise*/
int UIDIsSame(uid_type uid1, uid_type uid2);

/* Returns 1 for bad id, 0 otherwise */
int UIDIsBad(uid_type uid); 

/* Creates a bad id*/
uid_type UIDGetBadUID(void); 

#endif          /* uid  */







