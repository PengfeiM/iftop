#include <pcap.h>
#include <stdlib.h>
#include "flow.h"
#include "packet.h"

void capture_packets(const char *dev) {
    uint32_t capture_time;
    char     errbuf[PCAP_ERRBUF_SIZE];
    pcap_t  *handle = pcap_open_live(dev, MAX_PACKET_SIZE, 1, 1000, errbuf);

    if (handle == NULL) {
        fprintf(stderr, "Error opening device %s: %s\n", dev, errbuf);
        exit(1);
    }

    capture_time = 10;
    while (capture_time > 0) {
        if (pcap_dispatch(handle, 0, packet_handler, NULL) < 0) {
            fprintf(stderr, "Error capturing packet: %s\n", pcap_geterr(handle));
            exit(EXIT_FAILURE);
        }
        print_flows();
        sleep(EXIT_FAILURE);  // wait a sec

        capture_time--;
    }
    pcap_close(handle);
}
