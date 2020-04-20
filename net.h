/*
net.h contains data structures/APIs relataed to network config

Every node has its own IP address, called as loopback address
Every interface MUST have mac address, and MAY have ip-address/mask
*/

#ifndef __NET__
#define __NET__

#include <memory.h>
#include "utils.h"

typedef struct graph_ graph_t;
typedef struct node_ node_t;
typedef struct interface_ interface_t;

typedef struct ip_add_ {
    char ip_addr[16];
} ip_add_t;

typedef struct mac_add_ {
    char mac[8];
} mac_add_t;

typedef struct node_nw_prop_ {

    /* Used to find various device types capabilities of
     * the node and other features*/
    unsigned int flags;

    // L3 properties
    bool_t is_lb_addr_config;
    ip_add_t lb_addr; // loopback address of node
} node_nw_prop_t;

static inline void
init_node_nw_prop(node_nw_prop_t *node_nw_prop) {
    node_nw_prop->is_lb_addr_config = FALSE;
    memset(node_nw_prop->lb_addr.ip_addr, 0, 16);
}

typedef struct intf_nw_props_ {
    // L2 properties
    mac_add_t mac_add;

    // L3 properties
    bool_t is_ipadd_config;
    ip_add_t ip_add;
    char mask;
} intf_nw_props_t;

static inline void
init_intf_nw_prop(intf_nw_props_t *intf_nw_props) {
    memset(intf_nw_props->mac_add.mac, 0, 8);
    intf_nw_props->is_ipadd_config = FALSE;
    memset(intf_nw_props->ip_add.ip_addr, 0, 16);
    intf_nw_props->mask = 0;
}

void
interface_assign_mac_address(interface_t *interface);

// MAC/IP getter functions
#define IF_MAC(intf_ptr)    ((intf_ptr)->intf_nw_props.mac_add.mac)
#define IF_IP(intf_ptr)     ((intf_ptr)->intf_nw_props.ip_add.ip_addr)

// return loopback address configured to a node "node_ptr" is pointing at
#define NODE_LO_ADDR(node_ptr)  (node_ptr->node_nw_prop.lb_addr.ip_addr)

/*
Must evaluate to true if ip address is configured on an iterface
Note : Interface is said to be operating in L3 mode if it has an IP address configured
*/
#define IS_INTF_L3_MODE(intf_ptr)   ((intf_ptr)->intf_nw_props.is_ipadd_config)

// APIs to set Network Node properties
bool_t node_set_loopback_address(node_t *node, char *ip_addr);
bool_t node_set_intf_ip_address(node_t *node, char *local_if, char *ip_addr, char mask);
bool_t node_unset_intf_ip_address(node_t *node, char *local_if);

/*
return the pointer to local interface of a node such that this local
interface shares the same subnet as that of ip_addr
*/
interface_t *
node_get_matching_subnet_interface(node_t *node, char *ip_addr);

/*
convert ip address in string form into its equivalent 32-bit integer form
*/
unsigned int
convert_ip_from_str_to_int(char *ip_addr);

/*
convert ip address in integer form into its equivalent dot decimal form
*/
void
convert_ip_from_int_to_str(unsigned int ip_addr, char *output_buffer);


/*
Functions to dump network information on node/interface properties
*/
void dump_nw_graph(graph_t *graph);
void dump_node_nw_props(node_t *node);
void dump_intf_props(interface_t *interface);

#endif // __NET__