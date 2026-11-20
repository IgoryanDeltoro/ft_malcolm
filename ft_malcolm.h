#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H
# define ETH_ALEN 6
# include "./Libft_42/libft.h"
# include <linux/if_ether.h>
# include <netinet/if_ether.h>
# include <stdio.h>
# include <arpa/inet.h>

struct eth_header {
    uint8_t  dst_mac[6];   // destination MAC (where the frame goes)
    uint8_t  src_mac[6];   // source MAC (who sent it — spoofed in your reply)
    uint16_t ethertype;    // 0x0806 = ARP; written with htons()
} __attribute__((packed));

struct arp_packet {
    uint16_t htype;    // hardware type: 1 = Ethernet       (htons)
    uint16_t ptype;    // protocol type: 0x0800 = IPv4      (htons)
    uint8_t  hlen;     // hardware addr length: 6
    uint8_t  plen;     // protocol addr length: 4
    uint16_t oper;     // 1 = request, 2 = reply            (htons)
    uint8_t  sha[6];   // Sender Hardware Addr  (MAC)
    uint8_t  spa[4];   // Sender Protocol Addr  (IPv4)
    uint8_t  tha[6];   // Target Hardware Addr  (MAC)
    uint8_t  tpa[4];   // Target Protocol Addr  (IPv4)
} __attribute__((packed));

struct arp_frame {
    struct eth_header eth;   // 14 bytes
    struct arp_packet arp;   // 28 bytes
} __attribute__((packed));   // → 42 bytes total, ready to sendto()

typedef struct s_ctx {
    int           sockfd;            // the raw AF_PACKET socket fd
    unsigned int  ifindex;          // from if_nametoindex(), for sendto
    // char          ifname[IFNAMSIZ]; // chosen interface, e.g. "eth0"

    uint8_t       src_mac[6];       // arg 2 — the MAC you spoof
    uint8_t       src_ip[4];        // arg 1 — the IP you impersonate
    uint8_t       tgt_mac[6];       // arg 4 — the victim's MAC
    uint8_t       tgt_ip[4];        // arg 3 — the victim's IP
} t_ctx;

// volatile sig_atomic_t  g_stop = 0;   // set to 1 by the SIGINT handler

int parse_arguments(t_ctx *data, char **args);


#endif