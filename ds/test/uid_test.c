/*******************************************************************************
* Programmer: Avihay Asraf
* uid_test.c
* File: uid testing
* Date: ד' מאי 22 17:59:43 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */

#include "./include/uid.h"

#define RED       "\x1b[31m"
#define YELLOW    "\x1b[1;33m"  
#define CYAN      "\x1b[36m\x1b[1m"
#define GREEN     "\x1B[32m"
#define MAGENTA   "\x1B[35m"
#define WHITE     "\x1B[37m"
#define RESET     "\x1b[0m"

#define SUCCESS 0 
#define FAIL 1 

static int TestUIDIsGetBad(void);
static int TestUIDIsSame(void);




int main(void)
{
    size_t num_of_tests = 2; 
    size_t test_fail = 0; 
   
    if (FAIL == TestUIDIsGetBad())
    {
        puts(RED"Test Get bad uid"RESET);
        ++test_fail;
    }

    if(FAIL == TestUIDIsSame()) 
    {
        puts(RED"Test Is same UID fail"RESET);
        ++test_fail;
    }
    
    
    printf(CYAN"Test Performed : %ld\n"RESET, num_of_tests); 
    puts(YELLOW"-----------------------------"RESET);
    printf(GREEN"Test SUCCESS : %ld\n"RESET, num_of_tests - test_fail); 
    printf(RED"Test FAIL : %ld\n"RESET, test_fail); 
    
    return (EXIT_SUCCESS);
}


static int TestUIDIsGetBad(void)
{
    int fail = 0;
    
    ((1 == UIDIsBad(UIDGetBadUID())) ? (fail) : (++fail)); 
    ((0 == UIDIsBad(UIDCreate())) ? (fail) : (++fail));
     
    return (!(fail == 0));
}

static int TestUIDIsSame(void)
{
    int fail = 0; 
    uid_type uid1 = UIDCreate(); 
    uid_type uid2 = UIDCreate();
    
    (1 == (UIDIsSame(uid1, uid1)) ? (fail) : (++fail)); 
    (0 == (UIDIsSame(uid1, uid2)) ? (fail) : (++fail)); 
    return (!(fail == 0));
}





