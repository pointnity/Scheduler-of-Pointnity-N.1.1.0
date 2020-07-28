/********************************
 FileName: executor/ip_pool.cpp
 Version:  0.1
 Description: the pool of ip
*********************************/

// ip 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <vector>

#include <gflags/gflags.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "executor/ip_pool.h"
#include "common/clynn/string_utility.h"

using std::vector;
using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("executor");
