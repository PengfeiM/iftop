#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include "capture.h"

int main(int argc, char *argv[]) {
    printf("This is a demo for iftop");
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <interface>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    capture_packets(argv[1]);

    return EXIT_SUCCESS;
}
