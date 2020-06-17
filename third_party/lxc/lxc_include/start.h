#ifndef __lxc_state_h
#define __lxc_state_h

#include <lxc/state.h>
#include <sys/param.h>

struct lxc_conf;

struct lxc_handler;

struct lxc_operations {
	int (*start)(struct lxc_handler *, void *);
	int (*post_start)(struct lxc_handler *, void *);
};

struct lxc_handler {
