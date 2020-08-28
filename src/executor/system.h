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
#include <unistd.h>
// #include <netdb.h>
#include <string>
#include <errno.h>
#include <stdio.h>

using std::string;

class System {
public:
    /// @brief: Load 
    // get cpu average load(1 min)
    static double GetLoadAvginOne();

    // get cpu average load(5 min)
    static double GetLoadAvginFive();

    // get cpu average load(15 min)
