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

DECLARE_string(ip_range);

bool IPPool::Init() {
    vector<string> vec_ips;
    StringUtility::Split(FLAGS_ip_range.c_str(), vec_ips, "-");

    if (vec_ips.size() != 2) {
        LOG4CPLUS_ERROR(logger, "ip_range is illegal, ip_range:" << FLAGS_ip_range);
        return false;
