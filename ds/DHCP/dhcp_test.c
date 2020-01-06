/*******************************************************************************
* Programmer: Avihay Asraf
* dhcp_test.c
* File: dhcp testing
* Date: ד' יול  3 17:12:29 IDT 2019
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /* strcat, strlen, strcpy                   */

#include "dhcp.h"

static void TestDynamicIPAlloc(void);
static void TestStaticIPAlloc(void);
static void TestDHCPFree(void);
/* --------------------------------------------------------------------------- */
int main(void)
{
    TestDynamicIPAlloc();
    TestStaticIPAlloc();
    TestDHCPFree();

    return (EXIT_SUCCESS);
}

static void TestDynamicIPAlloc(void)
{
    ip_t ip_subnet = {0xf5, 0x20, 0x10, 0}; 
    ip_t ip_zero = {0};
    size_t i = 0; 
    __uint32_t mask = 0xffffff0; 
    dhcp_handle_t *dhcp = NULL; 
    
    dhcp = DHCPCreate(ip_subnet, mask);
    if (NULL == dhcp)
    {
        puts("Error creating line 40"); 
        return; 
    }
    for (i = 0; i < 100 ; ++i)
    {
        memset(ip_zero, 0, 4);
        if (0 == DHCPAllocIP(dhcp, ip_zero))
        {
            puts ("Dynamic alloc failed");
        }
    }

    if (DHCPCount(dhcp) != 100)
    {
        puts ("dyn alloc error");
    }

    DHCPDestroy(dhcp); 
}

static void TestStaticIPAlloc(void)
{ 
    ip_t ip_subnet = {0}; 
    ip_t ip_static = {0};
    unsigned char *writer = ip_static;
    size_t i = 0; 
    __uint32_t mask = 0xffffff0; 
    unsigned int tmp = 0xffff0000; 
    dhcp_handle_t *dhcp = NULL; 
    
    memcpy(ip_subnet, &tmp, sizeof(int)); 
    dhcp = DHCPCreate(ip_subnet, mask);
    if (NULL == dhcp)
    {
        puts ("error creating line 69");
        return; 
    }

    for (i = 10; i < 50; ++i)
    {
        *writer = i; 
        if(0 == DHCPAllocIP(dhcp, ip_static))
        {
            puts ("error static insert");
        }
    }

    if (40 != DHCPCount(dhcp))
    {
        puts ("error inserting staticlly");
    }

    DHCPDestroy(dhcp);
}

static void TestDHCPFree(void)
{

    ip_t ip_subnet = {0}; 
    ip_t ip_zero = {0};
    unsigned char to_free[4] = {15, 0, 0, 0};
    size_t i = 0; 
    __uint32_t mask = 0xffffff0; 
    unsigned int tmp = 0xffff0000; 
    dhcp_handle_t *dhcp = NULL; 
    
    memcpy(ip_subnet, &tmp, sizeof(int)); 
    dhcp = DHCPCreate(ip_subnet, mask);
    if (NULL == dhcp)
    {
        puts("Error creating line 40"); 
        return; 
    }

    for (i = 0; i < 100 ; ++i)
    {
        memset(ip_zero, 0, 4);
        if (0 == DHCPAllocIP(dhcp, ip_zero))
        {
            puts ("Dynamic alloc failed");
        }
    }

    if (DHCPCount(dhcp) != 100)
    {
        puts ("dyn alloc error");
    }

    for (i = 0; i < 50; i+=10)
    {
        to_free[0] = i; 
        DHCPFreeIP(dhcp, to_free);
    }
    
    if (95 == DHCPCount(dhcp))

    DHCPDestroy(dhcp); 
}




