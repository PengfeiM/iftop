#ifndef FLOW_H
#define FLOW_H

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <unistd.h>

// flow defination, ipv4 only fornow
typedef struct flow_info {
    char     src_ip[INET_ADDRSTRLEN];
    char     dst_ip[INET_ADDRSTRLEN];
    uint16_t src_port;
    uint16_t dst_port;
    uint64_t byte_count;
    uint64_t pkt_count;
} flow_info_t;

extern int         global_flows_used;
extern int         global_flows_total;
extern flow_info_t global_flows[1024];  // 1024 for now

void print_flows();
void update_flow(const struct ip *ip_header, const struct tcphdr *tcp_header, size_t packet_len);

#endif  // !FLOW_H
