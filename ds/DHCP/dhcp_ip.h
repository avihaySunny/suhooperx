/*******************************************************************************
* Programmer: Avihay
* dhcp_ip.h
* File: dhcp_ip header
* Date: ד' יול  3 17:13:45 IDT 2019
*******************************************************************************/

#ifndef __DHCP_IP_H__
#define __DHCP_IP_H__

typedef unsigned char ip_t[4]; 

/*returns range of addresses  */
size_t GetRangeOfIp(unsigned int range);

/* adds the 1 or 0 bit needed by route  */
void UpdateIP(ip_t ip, unsigned int bit);

/* returns 1 if ip is set to zero */
int IsZeroAddress(const ip_t ip);

/* prints ip in format of xxx. xxx. xxx. xxx */
void PrintIP(const ip_t ip);

/* returns the bit corrosponding to the given indx  */
int GetNextBit(const ip_t ip, int indx);

/* combines ip and subnet to form a complete ip address */
void PasteSubnetIP(ip_t subnet, ip_t address);

#endif          /* dhcp_ip  */







