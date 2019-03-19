/*
 * lxc: linux Container library
 */
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define __USE_GNU /* for *_CLOEXEC */

#include <fcntl.h>
#include <stdlib.h>

#include "log.h"
#include "caps.h"

#define LXC_LOG_PREFIX_SIZE	32
#define LXC_LOG_BUFFER_SIZE	512

int lxc_log_fd = -1;
static char log_prefix[LXC_LOG_PREFIX_SIZE] = "lxc";

lxc_log_define(lxc_log, lxc);

/*---------------------------------------------------------------------------*/
static int log_append_stderr(const struct lxc_log_appender *appender,
			     struct lxc_log_event *event)
{
	if (event->priority < LXC_LOG_PRIORITY_ERROR)
		return 0;

	fprintf(stderr, "%s: ", log_prefix);
	vfprintf(stderr, event->fmt, *event->vap);
	fprintf(stderr, "\n");
	return 0;
}

/*---------------------------------------------------------------------------*/
static int log_append_logfile(const struct lxc_log_appender *appender,
