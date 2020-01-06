/*******************************************************************************
* Programmer: Avihay Asraf
* dhcp.c
* File: dhcp code
* Date: 
*******************************************************************************/

#include <assert.h> 	    /* assert                                   */
#include <stdio.h> 		    /* printf                                   */
#include <stdlib.h> 	    /* EXIT_SUCCESS EXIT_FAILURE malloc realloc */
#include <string.h>         /*                                          */

#include "dhcp.h"

static size_t GetMaxCount(size_t height);

/* --------------------------------------------------------------------- */
struct dhcp
{
    trie_t *root; 
    ip_t subnet; 
    size_t max_height; 
    size_t count; 
};

/* --------------------------------------------------------------------- */
dhcp_handle_t *DHCPCreate(const ip_t subnet, __uint32_t mask)
{
    dhcp_handle_t *dhcp = (dhcp_handle_t*)malloc(sizeof(dhcp_handle_t));
    if (NULL == dhcp)
    {
        return NULL;
    } 

    dhcp->root = CreateTrieNode(0);
    if(dhcp->root == NULL)
    {
        free(dhcp);
        return NULL;
    }

    memcpy(dhcp->subnet, subnet, 4);
    dhcp->max_height = GetRangeOfIp(~0x0 ^ mask) - 1; 
    dhcp->count = GetMaxCount(dhcp->max_height);

    return dhcp;
}
/* --------------------------------------------------------------------- */
void DHCPDestroy(dhcp_handle_t *dhcp)
{
    assert(dhcp);

    TrieDestroy(dhcp->root);
    free(dhcp);
}
/* --------------------------------------------------------------------- */
int DHCPAllocIP(dhcp_handle_t *dhcp, ip_t static_ip)
{
    int status = 0; 

    assert(dhcp);

    if (!IsZeroAddress(static_ip))
    {
        if (InsertStaticIP(dhcp->root, static_ip, dhcp->max_height))
        {
            --dhcp->count;
            status = 1; 
        } 
    }

    if(InsertDynamicIP(dhcp->root, static_ip, dhcp->max_height) && !status)
    {
        --dhcp->count;
        status = 1; 
    }

    PasteSubnetIP(dhcp->subnet, static_ip);

    return status; 
}
/* --------------------------------------------------------------------- */
void DHCPFreeIP(dhcp_handle_t *dhcp, const ip_t ip_to_free)
{
    assert(dhcp);

    if(TrieFreeIP(dhcp->root, ip_to_free , dhcp->max_height - 1))
    {
        ++dhcp->count;
    }
}
/* --------------------------------------------------------------------- */
size_t DHCPCount(const dhcp_handle_t *dhcp)
{
    assert(dhcp);

    return dhcp->count;
}
/* --------------------------------------------------------------------- */
static size_t GetMaxCount(size_t height)
{
    size_t i = 0; 
    size_t max_count = 1; 
    for (i = 0; i < height; ++i)
    {
        max_count = (max_count << 1) | 1; 
    }
    
    return max_count;
}