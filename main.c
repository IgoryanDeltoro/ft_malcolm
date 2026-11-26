#include "ft_malcolm.h"

void	debug_print_struct(t_ctx *data)
{
	printf("Source IP  : %u.%u.%u.%u\n",
		data->src_ip[0], data->src_ip[1],
		data->src_ip[2], data->src_ip[3]);
	printf("Source MAC : %02x:%02x:%02x:%02x:%02x:%02x\n",
		data->src_mac[0], data->src_mac[1], data->src_mac[2],
		data->src_mac[3], data->src_mac[4], data->src_mac[5]);
	printf("Target IP  : %u.%u.%u.%u\n",
		data->tgt_ip[0], data->tgt_ip[1],
		data->tgt_ip[2], data->tgt_ip[3]);
	printf("Target MAC : %02x:%02x:%02x:%02x:%02x:%02x\n",
		data->tgt_mac[0], data->tgt_mac[1], data->tgt_mac[2],
		data->tgt_mac[3], data->tgt_mac[4], data->tgt_mac[5]);
}

int main (int c, char **args) {
    if (c != 5) {
        printf("ft_malcolm: error: bad input arguments!\n");
        printf("Example:  ./ft_malcolm 10.12.35.255 ff:bb:ff:ff:ee:ff 10.12.10.22 10:dd:a1:ee:bb:ea\n");
        return 1;
    }

    if (getuid() != 0) {
        printf("ft_malcolm: error: must be run as root (try sudo)\n");
        return 1;
    }

    t_ctx data;
    ft_bzero(&data, sizeof(t_ctx));

    if (parse_arguments(&data, args) == -1) 
        return 1;

    if (get_interface(&data) == -1)
        return 1;

    int sock_fd = create_arp_socket();
    if (sock_fd == -1) return 1;
    wait_for_arp_request(sock_fd, &data);

    debug_print_struct(&data);
    return 0;
}