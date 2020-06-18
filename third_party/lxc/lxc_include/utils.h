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
		sa.sa_sigaction = tty_##s##_handler; \
		sa.sa_flags = SA_SIGINFO; \
		sigfillset(&sa.sa_mask); \
		/* No error expected with sigaction. */ \
		sigaction(s, &sa, &lxc_tty_sa_##s); \

#define LXC_TTY_DEL_HANDLER(s) \
	do { \
		sigaction(s, &lxc_tty_sa_##s, NULL); \
