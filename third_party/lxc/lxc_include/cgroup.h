#ifndef _cgroup_h
#define _cgroup_h

#define MAXPRIOLEN 24

struct lxc_handler;
int lxc_cgroup_create(const char *name, pid_t pid);
int lxc_cgroup_destroy(const char *name);
int lxc_cgroup_path_get(char **path, const char *subsystem, const char *name);
int lxc_cgroup_nrtasks(const char *name);
int lxc_ns_is_mounted(void);
