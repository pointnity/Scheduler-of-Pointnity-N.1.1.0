#ifndef _caps_h
#define _caps_h

extern int lxc_caps_reset(void);
extern int lxc_caps_down(void);
extern int lxc_caps_up(void);
extern int lxc_caps_init(void);

#define lxc_priv(__lxc_function)			\
	({						\
		int __ret, __ret2, __errno = 0;		\
		__ret = lxc_caps_up();			\
		if (__ret)				\
			goto __out;			\
		__ret = __lxc_function;			\
		if (__ret)				\
			__errno = errno;		\
		__ret2 = lxc_caps_down();		\
	__out:	__ret ? errno = __errno,__ret : __ret2;	\
	})

#define lxc_unpriv(__lxc_function)		\
	({						\
		int __ret, __ret2, __errno = 0;		\
		__ret = lxc_caps_down();		\
		if (__ret)				\
			goto __out;			\
		__ret = __lxc_function;			\
		if (__ret)				\
			__errno = errno;		\
		__ret2 = lxc_caps_up();			\
	__out:	__ret ? errno = __errno,__ret : __ret2;	\
	})
#endif
