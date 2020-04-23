#include "utils.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

void apply_mask(char *prefix, char mask, char *str_prefix) {
    unsigned int binary_prefix = 0;
    if (binary_prefix == inet_pton(AF_INET, prefix, &binary_prefix) == 0) {
        printf("Invalid Address : %s\n", prefix);
        exit(1);
    }
    binary_prefix = htonl(binary_prefix);
    for (int i = 0; i < 32 - mask; i++) {
        // clear ith bit(i.e. set it to 0)
        binary_prefix &= ~(1 << i);
    }
    binary_prefix = ntohl(binary_prefix);
    // for IPv4, the buffer must be at least 16 bytes
    inet_ntop(AF_INET, (void *) &binary_prefix, str_prefix, 16);
}

void layer2_fill_with_broadcast_mac(char *mac_array) {
    unsigned int i = 0;
    unsigned int mac_array_length = 6;
    for(;i < mac_array_length; i++) {
        mac_array[i] = 0xFF;
    }
}



