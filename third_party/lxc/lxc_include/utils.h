#ifndef _utils_h
#define _utils_h

#define LXC_TTY_HANDLER(s) \
	static struct sigaction lxc_tty_sa_##s;				\
	static void tty_##s##_handler(int sig, siginfo_t *info, void *ctx) \
	{								\
		if (lxc_tty_sa_##s.sa_handler == SIG_DFL ||		\
		    lxc_tty_sa_##s.sa_handler == SIG_IGN)		\
			return;						\
		(*lxc_tty_sa_##s.sa_sigaction)(sig, info, ctx);	\
	}

#define LXC_TTY_ADD_HANDLER(s) \
	do { \
		struct sigaction sa; \
