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
