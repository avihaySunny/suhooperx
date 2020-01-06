/*******************************************************************************
* Programmer: Avihay
* trie.h
* File: trie header
* Date: ד' יול  3 17:13:34 IDT 2019
*******************************************************************************/

#ifndef __TRIE_H__
#define __TRIE_H__

#include "dhcp_ip.h"

typedef struct trie_node trie_t; 

/* creates a trie node, available  for use, returns null on failure */
trie_t *CreateTrieNode(); 

/* destroys all nodes */
void TrieDestroy(trie_t *root); 

/* return 0 on failure to insert , 1 on success*/
int InsertDynamicIP(trie_t *node, ip_t ip, size_t height);


/* return 0 on failure to insert , 1 on success*/
int InsertStaticIP(trie_t *node, ip_t static_ip, size_t height);


/* return 0 on failure to insert , 1 on success*/
int TrieFreeIP (trie_t *node, const ip_t ip_to_free, size_t indx);

#endif          /* trie  */ 







