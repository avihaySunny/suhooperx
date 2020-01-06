/*******************************************************************************
* Programmer: Avihay Asraf
* dhcp_ip_test.c
* File: dhcp_ip testing
* Date: ד' יול  3 17:13:45 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */
#include "dhcp_ip.h"

static void TestUpdateIP(void);
static void TestGetNextBit(void);

int main(void)
{
    TestUpdateIP();
    TestGetNextBit();

    return (EXIT_SUCCESS);
}

static void TestUpdateIP(void)
{
    ip_t ip = {0, 0, 0, 0};
    size_t i = 0; 

    for (i = 0; i < 8; ++i)
    {
        UpdateIP(ip, 1); 
    }

    if (ip[0] != 0xff)
    {
        puts("error updating");
    }
}

static void TestGetNextBit(void)
{
    ip_t ip = {0xff, 0xff, 0xff, 0xff};
    int i = 0;
    
    for (i = 31; i >= 0; --i)  
    {
        if (GetNextBit(ip, i) == 0)
        {
            puts ("error getting bit");
        }
    }
}






