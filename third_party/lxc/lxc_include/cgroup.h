#ifndef _cgroup_h
#define _cgroup_h

#define MAXPRIOLEN 24

struct lxc_handler;
int lxc_cgroup_create(const char *name, pid_t pid);
