#ifndef _utils_h
#define _utils_h

#define LXC_TTY_HANDLER(s) \
	static struct sigaction lxc_tty_sa_##s;				\
	static void tty_##s##_handler(int sig, siginfo_t *info, void *ctx) \
	{								\
