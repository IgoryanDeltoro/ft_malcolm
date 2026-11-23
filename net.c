#include "ft_malcolm.h"
//socket+iface

static int is_valid_iface(struct ifaddrs *ifa) {
    if (!ifa->ifa_name || !ifa->ifa_addr)
        return 0;
    if (!(ifa->ifa_flags & IFF_UP))
        return 0;
    if (ifa->ifa_flags & IFF_LOOPBACK)
        return 0;
    return 1;
}

int get_interface(t_ctx *data) {
    struct ifaddrs *ifaddr;

    if (getifaddrs(&ifaddr) == -1) {
        printf("Error: while getting interfaces\n");
        return -1;
    }

    for (struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (is_valid_iface(ifa)) {

            ft_strlcpy(data->ifname, ifa->ifa_name, IFNAMSIZ);
            data->ifindex = if_nametoindex(ifa->ifa_name);
            freeifaddrs(ifaddr);
            if (data->ifindex == 0)
                return -1;
            printf("Found available interface: %s\n", data->ifname);
			return (0);
        }
    }

    freeifaddrs(ifaddr);
    return -1;
}