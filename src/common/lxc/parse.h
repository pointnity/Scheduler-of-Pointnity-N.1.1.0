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

extern int lxc_file_for_each_line(const char *file, lxc_file_cb callback,
				  void* data);

extern int lxc_char_left_gc(char *buffer, size_t len);

extern int lxc_char_right_gc(char *buffer, size_t len);

extern int lxc_is_line_empty(char *line);

#endif
