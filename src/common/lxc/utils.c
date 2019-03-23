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
	void *srcaddr = NULL, *dstaddr;
	struct stat stat;
	int srcfd, dstfd, ret = -1;
	char c = '\0';

	dstfd = open(dstfile, O_CREAT | O_EXCL | O_RDWR, 0600);
	if (dstfd < 0) {
		SYSERROR("failed to creat '%s'", dstfile);
		goto out;
	}

	srcfd = open(srcfile, O_RDONLY);
	if (srcfd < 0) {
		SYSERROR("failed to open '%s'", srcfile);
		goto err;
	}

	if (fstat(srcfd, &stat)) {
		SYSERROR("failed to stat '%s'", srcfile);
		goto err;
	}

	if (!stat.st_size) {
		INFO("copy '%s' which is an empty file", srcfile);
		ret = 0;
		goto out_close;
	}

	if (lseek(dstfd, stat.st_size - 1, SEEK_SET) < 0) {
		SYSERROR("failed to seek dest file '%s'", dstfile);
		goto err;
	}

	/* fixup length */
	if (write(dstfd, &c, 1) < 0) {
		SYSERROR("failed to write to '%s'", dstfile);
		goto err;
	}

	srcaddr = mmap(NULL, stat.st_size, PROT_READ, MAP_SHARED, srcfd, 0L);
	if (srcaddr == MAP_FAILED) {
		SYSERROR("failed to mmap '%s'", srcfile);
		goto err;
	}

	dstaddr = mmap(NULL, stat.st_size, PROT_WRITE, MAP_SHARED, dstfd, 0L);
	if (dstaddr == MAP_FAILED) {
		SYSERROR("failed to mmap '%s'", dstfile);
		goto err;
	}

	ret = 0;
