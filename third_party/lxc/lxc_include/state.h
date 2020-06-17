#ifndef _state_h
#define _state_h

typedef enum {
	STOPPED, STARTING, RUNNING, STOPPING,
	ABORTING, FREEZING, FROZEN, THAWED, MAX_STATE,
} lxc_state_t;

extern int lxc_rmstate(const char *name);
extern lxc_state_t lxc_getstate(const char *name);
