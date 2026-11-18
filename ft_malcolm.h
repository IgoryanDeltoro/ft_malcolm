#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H
# include <linux/if_ether.h>
# include <netinet/if_ether.h>

struct ethhdr {
    unsigned char   h_dest[ETH_ALEN];       /* destination eth addr */
    unsigned char   h_source[ETH_ALEN];     /* source ether addr */
    __be16          h_proto;                /* packet type ID field */
} __attribute__((packed));

struct        ether_arp {
    struct      arphdr ea_hdr;              /* fixed-size header */
    u_int8_t    arp_sha[ETH_ALEN];          /* sender hardware address */
    u_int8_t    arp_spa[4];                 /* sender protocol address */
    u_int8_t    arp_tha[ETH_ALEN];          /* target hardware address */
    u_int8_t    arp_tpa[4];                 /* target protocol address */
};

#endif