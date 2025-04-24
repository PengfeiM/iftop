#include "packet.h"
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <pcap.h>
#include "flow.h"

// packet_handler process captured packets
void packet_handler(unsigned char *user_data, const struct pcap_pkthdr *pkthdr, const unsigned char *packet) {
    //parse ip
    struct ip *ip_hdr = (struct ip *)(packet + ETH_HEADER_LEN);
    if (ip_hdr->ip_p == IPPROTO_TCP) {
        struct tcphdr *tcp_hdr = (struct tcphdr *)(packet + ETH_HEADER_LEN + (ip_hdr->ip_hl << 2));
        update_flow(ip_hdr, tcp_hdr, pkthdr->len);
    } else if (ip_hdr->ip_p == IPPROTO_UDP) {
        struct udphdr *udp_hdr = (struct udphdr *)(packet + ETH_HEADER_LEN + (ip_hdr->ip_hl << 2));
        update_flow(ip_hdr, (struct tcphdr *)udp_hdr, pkthdr->len);
    }
}
