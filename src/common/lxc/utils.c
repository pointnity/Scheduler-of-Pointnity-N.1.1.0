/*
 * lxc: linux Container library
 */
#define _GNU_SOURCE
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/mount.h>
#include <dirent.h>
#include <fcntl.h>
#include <libgen.h>

#include "log.h"

lxc_log_define(lxc_utils, lxc);

int lxc_copy_file(const char *srcfile, const char *dstfile)
{
