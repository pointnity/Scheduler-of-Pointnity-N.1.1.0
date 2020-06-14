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
