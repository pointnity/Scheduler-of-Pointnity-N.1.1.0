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
#include <stdio.h>

using std::string;
#if 0
int get_ip(char* str) {
    addrinfo hint;
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_INET;
    hint.ai_flags = AI_CANONNAME;
