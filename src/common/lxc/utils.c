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

	memcpy(dstaddr, srcaddr, stat.st_size);

	munmap(dstaddr, stat.st_size);
out_mmap:
	if (srcaddr)
		munmap(srcaddr, stat.st_size);
out_close:
	close(dstfd);
	close(srcfd);
out:
	return ret;
err:
	unlink(dstfile);
	goto out_mmap;
}

static int mount_fs(const char *source, const char *target, const char *type)
{
	/* the umount may fail */
	if (umount(target))
		WARN("failed to unmount %s : %s", target, strerror(errno));

	if (mount(source, target, type, 0, NULL)) {
		ERROR("failed to mount %s : %s", target, strerror(errno));
		return -1;
	}

	DEBUG("'%s' mounted on '%s'", source, target);

	return 0;
}

extern int lxc_setup_fs(void)
{
	if (mount_fs("proc", "/proc", "proc"))
		return -1;

	if (mount_fs("shmfs", "/dev/shm", "tmpfs"))
		return -1;

	/* If we were able to mount /dev/shm, then /dev exists */
	if (access("/dev/mqueue", F_OK) && mkdir("/dev/mqueue", 0666)) {
		SYSERROR("failed to create '/dev/mqueue'");
		return -1;
	}

	if (mount_fs("mqueue", "/dev/mqueue", "mqueue"))
		return -1;

	return 0;
}

/* borrowed from iproute2 */
extern int get_u16(ushort *val, const char *arg, int base)
{
	unsigned long res;
	char *ptr;

	if (!arg || !*arg)
		return -1;

	res = strtoul(arg, &ptr, base);
	if (!ptr || ptr == arg || *ptr || res > 0xFFFF)
		return -1;

	*val = res;

	return 0;
}

extern int mkdir_p(char *dir, mode_t mode)
{
        int ret;
        char *d;

        if (!strcmp(dir, "/"))
                return 0;

        d = strdup(dir);
        if (!d)
                return -1;

        ret = mkdir_p(dirname(d), mode);
        free(d);
        if (ret)
                return -1;

        if (!access(dir, F_OK))
                return 0;

        if (mkdir(dir, mode)) {
                SYSERROR("failed to create directory '%s'\n", dir);
                return -1;
        }

        return 0;
}
