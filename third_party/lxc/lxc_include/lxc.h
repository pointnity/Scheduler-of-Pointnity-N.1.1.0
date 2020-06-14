#ifndef __lxc_h
#define __lxc_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <lxc/state.h>

struct lxc_msg;
struct lxc_conf;

/**
 Following code is for liblxc.

 lxc/lxc.h will contain exports of liblxc
 **/

/*
 * Start the specified command inside a container
 * @name     : the name of the container
 * @argv     : an array of char * corresponding to the commande line
 * @conf     : configuration
 * Returns 0 on sucess, < 0 otherwise
 */
extern int lxc_start(const char *name, char *const argv[], struct lxc_conf *conf);

/*
 * Stop the container previously started with lxc_start, all
 * the processes running inside this container will be killed.
 * @name : the name of the container
 * Returns 0 on success, < 0 otherwise
 */
extern int lxc_stop(const char *name);

/*
 * Open the monitoring mechanism for a specific container
 * The function will return an fd corresponding to the events
 * Returns a file descriptor on success, < 0 otherwise
 */
extern int lxc_monitor_open(void);

/*
 * Read the state of the container if this one has changed
 * The function will block until there is an event available
 * @fd : the file descriptor provided by lxc_monitor_open
 * @state : the variable which will be filled with the state
 * Returns 0 if the monitored container has exited, > 0 if
 * data was readen, < 0 otherwise
 */
extern int lxc_monitor_read(int fd, struct lxc_msg *msg);

/*
 * Close the fd associated with the monitoring
 * @fd : the file descriptor provided by lxc_monitor_open
 * Returns 0 on success, < 0 otherwise
 */
extern int lxc_monitor_close(int fd);

/*
 * Show the console of the container.
 * @name : the name of container
 * @tty  : the tty number
 * @fd   : a pointer to a tty file descriptor
