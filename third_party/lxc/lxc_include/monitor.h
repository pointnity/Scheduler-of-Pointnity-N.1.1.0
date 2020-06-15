#ifndef __monitor_h
#define __monitor_h

#include <sys/param.h>

typedef enum {
	lxc_msg_state,
	lxc_msg_priority,
} lxc_msg_type_t;

struct lxc_msg {
	lxc_msg_type_t type;
	char name[MAXPATHLEN];
	int value;
};
