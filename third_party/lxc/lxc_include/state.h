#ifndef _state_h
#define _state_h

typedef enum {
	STOPPED, STARTING, RUNNING, STOPPING,
	ABORTING, FREEZING, FROZEN, THAWED, MAX_STATE,
} lxc_state_t;

extern int lxc_rmstate(const char *name);
extern lxc_state_t lxc_getstate(const char *name);

extern lxc_state_t lxc_str2state(const char *state);
extern const char *lxc_state2str(lxc_state_t state);

#endif
