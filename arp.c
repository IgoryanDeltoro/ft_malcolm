#include "ft_malcolm.h"
//build/parse frames

static void	print_request_info(struct arp_packet *pkt)
{
	char	ip_str[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, pkt->spa, ip_str, INET_ADDRSTRLEN);
	printf("An ARP request has been broadcast.\n");
	printf("\tmac address of request: %02x:%02x:%02x:%02x:%02x:%02x\n",
		pkt->sha[0], pkt->sha[1], pkt->sha[2],
		pkt->sha[3], pkt->sha[4], pkt->sha[5]);
	printf("\tIP address of request: %s\n", ip_str);
}

static int is_matching_request(struct arp_packet *frame, t_ctx *data) {
    if (ntohs(frame->oper) != 1)
        return 0;
    if (ft_memcmp(frame->spa, data->tgt_ip, 4) != 0)
        return 0;
    if (ft_memcmp(frame->sha, data->tgt_mac, 6) != 0)
        return 0;
    if (ft_memcmp(frame->tpa, data->src_ip, 4) != 0)
        return 0;
    return 1;
}

int wait_for_arp_request(int sock_fd, t_ctx *data) {
    uint8_t             buf[ETH_FRAME_LEN];
    ssize_t	            bytes;
    struct arp_packet   *frame;

    while (1) {
        bytes = recvfrom(sock_fd, buf, ETH_FRAME_LEN, 0, NULL, NULL);
        if (bytes == -1)
	    {
		    printf("ft_malcolm: recvfrom: %s\n", strerror(errno));
		    return (-1);
	    }
        if((size_t)bytes < sizeof(struct arp_packet)) 
            continue;

        frame = (struct arp_packet*)&buf;
        if (is_matching_request(frame, data)) {
            print_request_info(frame);
            break;
        }
    }
    return 0;
}