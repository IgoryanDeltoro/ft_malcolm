#include "ft_malcolm.h"

static void	free_memory(char **arr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int mac_validation(uint8_t *mac_addr, char *mac_str) {
    const size_t mac_len = 17;
    int colons = 0;
    char **hex_pairs = NULL;

    //check MAC's lenght
    if (ft_strlen(mac_str) != mac_len) return -1;

    // check colons
    for (size_t i = 0; i < mac_len; i++) {
        if (mac_str[i] == ':') colons++;     
    }
    if (colons != 5) return -1;

    // split MAC by colons
    hex_pairs = ft_split(mac_str, ':');
    if (!hex_pairs) return -1;

    // validate hex parts and convert into uint8_t
    for (int k = 0; k < 6; k++) {
        if (ft_strlen(hex_pairs[k]) != 2) {
            free_memory(hex_pairs, 6);
            return -1;
        }

        int par = ft_atoi_base(hex_pairs[k], 16);
        if (par == -1) {
            free_memory(hex_pairs, 6);
            return -1;
        }
        mac_addr[k] = (uint8_t)par;
    }
    free_memory(hex_pairs, 6);
    return 0;
}

int parse_arguments(t_ctx *data, char **args) {
    // pars and validate IPv4
    if (inet_pton(AF_INET, args[1], data->src_ip) <= 0) {
        printf("unknown host or invalid IP address: (%s)\n", args[1]);
        return -1;
    }
    if (inet_pton(AF_INET, args[3], data->tgt_ip) <= 0) {
        printf("unknown host or invalid IP address: (%s)\n", args[3]);
        return -1;
    }

    //parse and validate MAC
    if (mac_validation(data->src_mac, args[2]) < 0) {
        printf("invalid mac address: (%s)\n", args[2]);
        return -1;
    }
    if (mac_validation(data->tgt_mac, args[4]) < 0){
        printf("invalid mac address: (%s)\n", args[4]);
        return -1;
    }
    return 0;
} 