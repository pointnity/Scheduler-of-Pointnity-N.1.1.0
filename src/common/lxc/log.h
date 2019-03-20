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
};

/*
 * Returns true if the chained priority is equal to or higher than
 * given priority.
 */
static inline int
lxc_log_priority_is_enabled(const struct lxc_log_category* category,
			   int priority)
{
	while (category->priority == LXC_LOG_PRIORITY_NOTSET &&
	       category->parent)
		category = category->parent;

	return priority >= category->priority;
}

/*
 * converts a priority to a literal string
*/
static inline const char* lxc_log_priority_to_string(int priority)
{
	switch (priority) {
	case LXC_LOG_PRIORITY_TRACE:	return "TRACE";
	case LXC_LOG_PRIORITY_DEBUG:	return "DEBUG";
	case LXC_LOG_PRIORITY_INFO:	return "INFO";
	case LXC_LOG_PRIORITY_NOTICE:	return "NOTICE";
	case LXC_LOG_PRIORITY_WARN:	return "WARN";
	case LXC_LOG_PRIORITY_ERROR:	return "ERROR";
	case LXC_LOG_PRIORITY_CRIT:	return "CRIT";
	case LXC_LOG_PRIORITY_ALERT:	return "ALERT";
	case LXC_LOG_PRIORITY_FATAL:	return "FATAL";
	default:
		return "NOTSET";
	}
}
/*
 * converts a literal priority to an int
 */
static inline int lxc_log_priority_to_int(const char* name)
