/********************************
 FileName: executor/system.h
 Version:  0.1
 Description: get the physical resource info of the machine
*********************************/

#ifndef SRC_EXECUTOR_SYSTEM_H
#define SRC_EXECUTOR_SYSTEM_H

#include <iostream>
#include <stdint.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <net/if.h>
