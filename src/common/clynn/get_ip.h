#ifndef COMMON_GET_IP_H
#define COMMON_GET_IP_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <errno.h>
