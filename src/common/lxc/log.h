/*
 * lxc: linux Container library
 */
#ifndef _log_h
#define _log_h

#include <stdarg.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#ifndef O_CLOEXEC
#define O_CLOEXEC 02000000
#endif

#ifndef F_DUPFD_CLOEXEC
#define F_DUPFD_CLOEXEC 1030
#endif

#define LXC_LOG_PREFIX_SIZE	32
#define LXC_LOG_BUFFER_SIZE	512

/* predefined priorities. */
enum {
	LXC_LOG_PRIORITY_TRACE,
	LXC_LOG_PRIORITY_DEBUG,
	LXC_LOG_PRIORITY_INFO,
	LXC_LOG_PRIORITY_NOTICE,
	LXC_LOG_PRIORITY_WARN,
	LXC_LOG_PRIORITY_ERROR,
	LXC_LOG_PRIORITY_CRIT,
	LXC_LOG_PRIORITY_ALERT,
	LXC_LOG_PRIORITY_FATAL,
	LXC_LOG_PRIORITY_NOTSET,
};

/* location information of the logging event */
struct lxc_log_locinfo {
	const char	*file;
	const char	*func;
	int		line;
};

#define LXC_LOG_LOCINFO_INIT
	{ .file = __FILE__, .func = __func__, .line = __LINE__	}

/* brief logging event object */
struct lxc_log_event {
	const char*		category;
	int			priority;
	struct timeval		timestamp;
	struct lxc_log_locinfo	*locinfo;
	const char		*fmt;
	va_list			*vap;
};

/* log appender object */
struct lxc_log_appender {
	const char*	name;
	int (*append)(const struct lxc_log_appender *, struct lxc_log_event *);

	/*
	 * appenders can be stacked
	 */
	struct lxc_log_appender	*next;
};

/* log category object */
struct lxc_log_category {
	const char			*name;
	int				priority;
	struct lxc_log_appender		*appender;
	const struct lxc_log_category	*parent;
