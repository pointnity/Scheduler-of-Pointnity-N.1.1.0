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
	pid_t pid;
	char *name;
	lxc_state_t state;
	int sigfd;
	sigset_t oldmask;
	struct lxc_conf *conf;
	struct lxc_operations *ops;
	void *data;
	int sv[2];
};

extern struct lxc_handler *lxc_init(const char *name, struct lxc_conf *);
extern int lxc_spawn(struct lxc_handler *);

extern int lxc_poll(const char *name, struct lxc_handler *handler);
extern void lxc_abort(const char *name, struct lxc_handler *handler);
extern void lxc_fini(const char *name, struct lxc_handler *handler);
