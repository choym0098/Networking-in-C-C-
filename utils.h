#ifndef __ENUM__
#define __ENUM__



typedef enum{
    FALSE,
    TRUE
} bool_t;

/*
apply mask on prefix and store result in str_prefix
prefix      : a pointer to IP address string
make        : subnet mask - any integer [0 - 32]
str_prefix  : stores masked prefix
*/
void
apply_mask(char *prefix, char mask, char *str_prefix);

/*
(A broad caast mac address is a 6 byte mac address with all bits set to 1)
fill the 6-byte array with MAC broadcasat address
*/
void
layer2_fill_with_broadcast_mac(char *mac_array);

/*
evaluate to true if the mac address is BROADCAST mac address, otherwise FALSE.
*/
#define IS_MAC_BROADCAST_ADDR(mac) \
    (mac[0] == 0xFF && mac[1] == 0xFF && mac[2] == 0xFF && \
     mac[3] == 0xFF && mac[4] == 0xFF && mac[5] == 0xFF && )







#endif // __ENUM__