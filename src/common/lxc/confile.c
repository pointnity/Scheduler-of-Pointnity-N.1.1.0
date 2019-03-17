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
