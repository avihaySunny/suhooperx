/*******************************************************************************
* Programmer: Avihay
* dhcp.h
* File: dhcp header
* Date: ד' יול  3 17:12:29 IDT 2019
*******************************************************************************/

#ifndef __DHCP_H__
#define __DHCP_H__

#include "dhcp_ip.h"
#include "trie.h"

typedef struct dhcp dhcp_handle_t; 

dhcp_handle_t *DHCPCreate(const ip_t subnet, __uint32_t mask);

void DHCPDestroy(dhcp_handle_t *dhcp); 

int DHCPAllocIP(dhcp_handle_t *dhcp,  ip_t static_ip); 

void DHCPFreeIP(dhcp_handle_t *dhcp, const ip_t ip_to_free); 

size_t DHCPCount(const dhcp_handle_t *dhcp);


#endif          /* dhcp  */







