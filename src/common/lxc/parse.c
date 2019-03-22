/*
 * lxc: linux Container library
 */
#define _GNU_SOURCE
#include <stdio.h>
#undef _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

#include "parse.h"
#include <lxc/log.h>

lxc_log_define(lxc_parse, lxc);

static int dir_filter(const struct dirent *dirent)
{
	if (!strcmp(dirent->d_name, ".") ||
            !strcmp(dirent->d_name, ".."))
                return 0;
        return 1;
}

int lxc_dir_for_each(const char *name, const char *directory,
		     lxc_dir_cb callback, void *data)
{
	struct dirent **namelist;
