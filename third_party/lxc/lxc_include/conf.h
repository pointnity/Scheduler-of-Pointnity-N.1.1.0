#ifndef _conf_h
#define _conf_h

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>
#include <sys/param.h>

#include <lxc/list.h>

#include <lxc/start.h> /* for lxc_handler */

enum {
	LXC_NET_EMPTY,
	LXC_NET_VETH,
	LXC_NET_MACVLAN,
	LXC_NET_PHYS,
	LXC_NET_VLAN,
	LXC_NET_MAXCONFTYPE,
};

/*
 * Defines the structure to configure an ipv4 address
 * @address   : ipv4 address
 * @broadcast : ipv4 broadcast address
