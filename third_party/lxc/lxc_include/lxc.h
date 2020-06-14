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
