#include "utils.h"
#include <arpa/inet.h>

/*
apply mask on prefix and stores masked prefix in str_prefix
prefix : ip address in text form
mask : subnet mask applied to prefix to get network ID
str_prefix : sotres masked prefix
*/
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


