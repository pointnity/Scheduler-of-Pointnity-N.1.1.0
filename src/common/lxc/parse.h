/*
 * lxc: linux Container library
 */
#ifndef __parse_h
#define __parse_h

typedef int (*lxc_dir_cb)(const char *name, const char *directory,
			  const char *file, void *data);

typedef int (*lxc_file_cb)(char *buffer, void *data);

extern int lxc_dir_for_each(const char *name, const char *directory,
			    lxc_dir_cb callback, void *data);
