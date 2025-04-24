#include "flow.h"
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int         global_flows_used  = 0;
int         global_flows_total = 1024;
flow_info_t global_flows[1024];  // ✅ 真正定义 + 分配内存

void print_flows() {
    printf("\n--- flow stats ---\n");
    for (int i = 0; i < global_flows_used; i++) {
        printf("src_ip: %s, dst_ip: %s, src_port: %u, dst_port: %u, "
               "total_bytes: %llu, total_pkts: %llu\n",
               global_flows[i].src_ip, global_flows[i].dst_ip, global_flows[i].src_port, global_flows[i].dst_port,
               global_flows[i].byte_count, global_flows[i].pkt_count);
    }
    printf("\n");
}

void update_flow(const struct ip *ip_header, const struct tcphdr *tcp_header, size_t packet_len) {
    // ip + port -> flow
    char src_ip[INET_ADDRSTRLEN];
    char dst_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ip_header->ip_src), src_ip, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &(ip_header->ip_dst), dst_ip, INET_ADDRSTRLEN);

    uint16_t src_port = ntohs(tcp_header->th_sport);
    uint16_t dst_port = ntohs(tcp_header->th_dport);

    // update
    for (int i = 0; i < global_flows_used; i++) {
        if (strcmp(global_flows[i].src_ip, src_ip) == 0 && strcmp(global_flows[i].dst_ip, dst_ip) == 0 &&
            global_flows[i].src_port == src_port && global_flows[i].dst_port == dst_port) {
            global_flows[i].byte_count += packet_len;
            global_flows[i].pkt_count++;
            return;
        }
    }

    if (global_flows_used < global_flows_total) {
        strcpy(global_flows[global_flows_used].src_ip, src_ip);
        strcpy(global_flows[global_flows_used].dst_ip, dst_ip);
        global_flows[global_flows_used].src_port = src_port;
        global_flows[global_flows_used].dst_port = dst_port;
        global_flows_used++;
    }
}
