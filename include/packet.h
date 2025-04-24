/**
 * this is a head file for packet
 */

#ifndef PACKET_H
#define PACKET_H


#include <netinet/ip.h>
#include <pcap.h>

/*#define MAX_PACKET_SIZE 1 << 16 - 1  // MAX_PACKET_SIZE max size of a network packet*/
#define MAX_PACKET_SIZE IP_MAXPACKET
#define ETH_HEADER_LEN 14

// calculate ip header's length
#define IP_HEADER_LEN(ip_header) ((ip_header)->ip_hl * 4)

void packet_handler(unsigned char *user_data, const struct pcap_pkthdr *pkthdr, const unsigned char *packet);

#endif // !PACKET_H
