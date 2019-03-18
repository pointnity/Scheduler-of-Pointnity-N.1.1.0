/*
 * linux Container library
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pty.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/utsname.h>
#include <sys/personality.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>

#include "parse.h"
#include "utils.h"

#include <lxc/log.h>
#include <lxc/conf.h>

lxc_log_define(lxc_confile, lxc);

static int config_personality(const char *, char *, struct lxc_conf *);
static int config_pts(const char *, char *, struct lxc_conf *);
static int config_tty(const char *, char *, struct lxc_conf *);
static int config_cgroup(const char *, char *, struct lxc_conf *);
static int config_mount(const char *, char *, struct lxc_conf *);
static int config_rootfs(const char *, char *, struct lxc_conf *);
static int config_rootfs_mount(const char *, char *, struct lxc_conf *);
static int config_pivotdir(const char *, char *, struct lxc_conf *);
static int config_utsname(const char *, char *, struct lxc_conf *);
static int config_network_type(const char *, char *, struct lxc_conf *);
static int config_network_flags(const char *, char *, struct lxc_conf *);
static int config_network_link(const char *, char *, struct lxc_conf *);
static int config_network_name(const char *, char *, struct lxc_conf *);
static int config_network_veth_pair(const char *, char *, struct lxc_conf *);
static int config_network_macvlan_mode(const char *, char *, struct lxc_conf *);
static int config_network_hwaddr(const char *, char *, struct lxc_conf *);
static int config_network_vlan_id(const char *, char *, struct lxc_conf *);
static int config_network_mtu(const char *, char *, struct lxc_conf *);
static int config_network_ipv4(const char *, char *, struct lxc_conf *);
static int config_network_script(const char *, char *, struct lxc_conf *);
static int config_network_ipv6(const char *, char *, struct lxc_conf *);
static int config_cap_drop(const char *, char *, struct lxc_conf *);
static int config_console(const char *, char *, struct lxc_conf *);

typedef int (*config_cb)(const char *, char *, struct lxc_conf *);

struct config {
	char *name;
	config_cb cb;
};

static struct config config[] = {

	{ "lxc.arch",                 config_personality          },
	{ "lxc.pts",                  config_pts                  },
	{ "lxc.tty",                  config_tty                  },
	{ "lxc.cgroup",               config_cgroup               },
	{ "lxc.mount",                config_mount                },
	{ "lxc.rootfs.mount",         config_rootfs_mount         },
	{ "lxc.rootfs",               config_rootfs               },
	{ "lxc.pivotdir",             config_pivotdir             },
	{ "lxc.utsname",              config_utsname              },
	{ "lxc.network.type",         config_network_type         },
	{ "lxc.network.flags",        config_network_flags        },
	{ "lxc.network.link",         config_network_link         },
	{ "lxc.network.name",         config_network_name         },
	{ "lxc.network.macvlan.mode", config_network_macvlan_mode },
	{ "lxc.network.veth.pair",    config_network_veth_pair    },
	{ "lxc.network.script.up",    config_network_script       },
	{ "lxc.network.hwaddr",       config_network_hwaddr       },
	{ "lxc.network.mtu",          config_network_mtu          },
	{ "lxc.network.vlan.id",      config_network_vlan_id      },
	{ "lxc.network.ipv4",         config_network_ipv4         },
	{ "lxc.network.ipv6",         config_network_ipv6         },
	{ "lxc.cap.drop",             config_cap_drop             },
	{ "lxc.console",              config_console              },
};

static const size_t config_size = sizeof(config)/sizeof(struct config);

static struct config *getconfig(const char *key)
{
	int i;

	for (i = 0; i < config_size; i++)
		if (!strncmp(config[i].name, key,
			     strlen(config[i].name)))
			return &config[i];
	return NULL;
}

static int config_network_type(const char *key, char *value,
			       struct lxc_conf *lxc_conf)
{
	struct lxc_list *network = &lxc_conf->network;
	struct lxc_netdev *netdev;
	struct lxc_list *list;

	netdev = malloc(sizeof(*netdev));
	if (!netdev) {
		SYSERROR("failed to allocate memory");
		return -1;
	}

	memset(netdev, 0, sizeof(*netdev));
	lxc_list_init(&netdev->ipv4);
	lxc_list_init(&netdev->ipv6);

	list = malloc(sizeof(*list));
	if (!list) {
		SYSERROR("failed to allocate memory");
		return -1;
	}

	lxc_list_init(list);
	list->elem = netdev;

	lxc_list_add_tail(network, list);

	if (!strcmp(value, "veth"))
		netdev->type = LXC_NET_VETH;
	else if (!strcmp(value, "macvlan"))
		netdev->type = LXC_NET_MACVLAN;
	else if (!strcmp(value, "vlan"))
		netdev->type = LXC_NET_VLAN;
	else if (!strcmp(value, "phys"))
		netdev->type = LXC_NET_PHYS;
	else if (!strcmp(value, "empty"))
		netdev->type = LXC_NET_EMPTY;
	else {
		ERROR("invalid network type %s", value);
		return -1;
	}
	return 0;
}

static int config_ip_prefix(struct in_addr *addr)
{
	if (IN_CLASSA(addr->s_addr))
		return 32 - IN_CLASSA_NSHIFT;
	if (IN_CLASSB(addr->s_addr))
		return 32 - IN_CLASSB_NSHIFT;
	if (IN_CLASSC(addr->s_addr))
		return 32 - IN_CLASSC_NSHIFT;

	return 0;
}

static struct lxc_netdev *network_netdev(const char *key, const char *value,
					 struct lxc_list *network)
{
	struct lxc_netdev *netdev;

	if (lxc_list_empty(network)) {
		ERROR("network is not created for '%s' = '%s' option",
		      key, value);
		return NULL;
	}

	netdev = lxc_list_last_elem(network);
	if (!netdev) {
		ERROR("no network device defined for '%s' = '%s' option",
		      key, value);
		return NULL;
	}

	return netdev;
}

static int network_ifname(char **valuep, char *value)
{
	if (strlen(value) >= IFNAMSIZ) {
		ERROR("invalid interface name: %s", value);
		return -1;
	}

	*valuep = strdup(value);
	if (!*valuep) {
		ERROR("failed to dup string '%s'", value);
		return -1;
	}

	return 0;
}

#ifndef MACVLAN_MODE_PRIVATE
#  define MACVLAN_MODE_PRIVATE 1
#endif

#ifndef MACVLAN_MODE_VEPA
#  define MACVLAN_MODE_VEPA 2
#endif

#ifndef MACVLAN_MODE_BRIDGE
#  define MACVLAN_MODE_BRIDGE 4
#endif

static int macvlan_mode(int *valuep, char *value)
{
	struct mc_mode {
		char *name;
		int mode;
	} m[] = {
		{ "private", MACVLAN_MODE_PRIVATE },
		{ "vepa", MACVLAN_MODE_VEPA },
		{ "bridge", MACVLAN_MODE_BRIDGE },
	};

	int i;

	for (i = 0; i < sizeof(m)/sizeof(m[0]); i++) {
		if (strcmp(m[i].name, value))
			continue;

		*valuep = m[i].mode;
		return 0;
	}

	return -1;
}

static int config_network_flags(const char *key, char *value,
				struct lxc_conf *lxc_conf)
{
	struct lxc_netdev *netdev;

	netdev = network_netdev(key, value, &lxc_conf->network);
	if (!netdev)
		return -1;

	netdev->flags |= IFF_UP;

	return 0;
}

static int config_network_link(const char *key, char *value,
			       struct lxc_conf *lxc_conf)
{
	struct lxc_netdev *netdev;

	netdev = network_netdev(key, value, &lxc_conf->network);
	if (!netdev)
		return -1;

	return network_ifname(&netdev->link, value);
}

static int config_network_name(const char *key, char *value,
			       struct lxc_conf *lxc_conf)
{
	struct lxc_netdev *netdev;

	netdev = network_netdev(key, value, &lxc_conf->network);
	if (!netdev)
		return -1;

	return network_ifname(&netdev->name, value);
}

static int config_network_veth_pair(const char *key, char *value,
				    struct lxc_conf *lxc_conf)
{
	struct lxc_netdev *netdev;

	netdev = network_netdev(key, value, &lxc_conf->network);
	if (!netdev)
		return -1;

	return network_ifname(&netdev->priv.veth_attr.pair, value);
}

static int config_network_macvlan_mode(const char *key, char *value,
				       struct lxc_conf *lxc_conf)
{
	struct lxc_netdev *netdev;

	netdev = network_netdev(key, value, &lxc_conf->network);
	if (!netdev)
		return -1;

	return macvlan_mode(&netdev->priv.macvlan_attr.mode, value);
}

static int config_network_hwaddr(const char *key, char *value,
				 struct lxc_conf *lxc_conf)
{
	struct lxc_netdev *netdev;

	netdev = network_netdev(key, value, &lxc_conf->network);
	if (!netdev)
		return -1;

	netdev->hwaddr = strdup(value);
	if (!netdev->hwaddr) {
		SYSERROR("failed to dup string '%s'", value);
		return -1;
	}

	return 0;
}

static int config_network_vlan_id(const char *key, char *value,
			       struct lxc_conf *lxc_conf)
{
	struct lxc_netdev *netdev;

	netdev = network_netdev(key, value, &lxc_conf->network);
	if (!netdev)
		return -1;

	if (get_u16(&netdev->priv.vlan_attr.vid, value, 0))
		return -1;

	return 0;
