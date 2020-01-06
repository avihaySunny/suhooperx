/*******************************************************************************
* Programmer: Avihay Asraf
* dhcp_ip.c
* File: dhcp_ip code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#include "dhcp_ip.h"
#include "bits_array.h" 

size_t GetRangeOfIp(unsigned int range)
{
    size_t count = 0; 
    while (range != 0)
    {
        count += range & 1;
        range = range >> 1; 
    }

    return count; 
}

void UpdateIP(ip_t ip, unsigned int bit)
{
    unsigned long *ip_ptr = (unsigned long *)ip;
    *ip_ptr = (*ip_ptr << 1) + bit; 
}

int IsZeroAddress(const ip_t ip)
{
    int i = 0; 
    unsigned char *ip_ptr = (unsigned char*)ip;
    for (i = 0; i < 4; ++i)
    {
        if (*ip_ptr != 0)
        {
            return 0; 
        }

        ++ip_ptr;
    } 
    
    return 1; 
}

void PrintIP(const ip_t ip)
{
    size_t i = 0;
    unsigned char *ip_ptr = (unsigned char*)ip ;

    for (i = 0; i < 4; ++i)
    {
        printf("%d.", *ip_ptr);
        ++ip_ptr;
    }
}

int GetNextBit(const ip_t ip, int indx)
{ 
    unsigned long *ip_ptr = (unsigned long*)ip; 
    return (*ip_ptr >> indx) & 1;     
}

void PasteSubnetIP(ip_t subnet, ip_t address)
{
    unsigned char *sub_ptr = subnet; 
    unsigned char *add_ptr = address;
    size_t i = 0; 
    add_ptr += 3; 
    
    for (i = 0; i < 4; ++i)
    {
        *add_ptr = *sub_ptr + *add_ptr;
        --add_ptr;
        ++sub_ptr; 
    }
}