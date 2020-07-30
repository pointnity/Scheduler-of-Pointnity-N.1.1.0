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
    }

    int32_t ip_start = iptoint(vec_ips[0].c_str());
    if (-1 == ip_start) {
        LOG4CPLUS_ERROR(logger, "ip_start is illegal, ip_start:" << vec_ips[0]);
        return false;
    }

    int32_t ip_end = iptoint(vec_ips[1].c_str());
    if (-1 == ip_end) {
        LOG4CPLUS_ERROR(logger, "ip_end is illegal, ip_end:" << vec_ips[1]);
        return false;
    } 

    int32_t ip_number = ip_end - ip_start + 1;
    for (int32_t i = 0; i < ip_number; ++i) { 
        int32_t int_ip = ip_start + i;
        string ip = inttoip(int_ip);
        if (ip.empty()) {
            LOG4CPLUS_ERROR(logger, "Failed to trans int_ip to string_ip, int_ip:" << ip_start + i);
            return false;
        }
        m_ip_map[string(ip)] = true; 
    }
    return true;
}

int32_t IPPool::iptoint(const char *ip ) {
    if (INADDR_NONE == ip_num) {
        LOG4CPLUS_ERROR(logger, "ip is illegal, ip:" << ip);
        return -1;
    }
    return ntohl(ip_num);
}

string IPPool::inttoip(int ip_num) {
    struct in_addr addr;
    struct in_addr addr;
    addr.s_addr = htonl(ip_num);
    char * ip;
    ip = inet_ntoa(addr);
    if (!ip) {
        string null_str;
        return null_str;
    }

    return string(ip);
}

// TODO just for test
void IPPool::PrintAll() {
    ReadLocker locker(m_lock);
    printf("ip_pool.cpp\n");
    printf("************ IPs ************\n");
    for (map<string, bool>::iterator it = m_ip_map.begin();
         it != m_ip_map.end(); ++it) {
        string avail = "avail";
        if (!(it->second))
            avail = "not avail";
        printf("IP: %s, %s\n", it->first.c_str(), avail.c_str());
    }
    printf("*****************************\n");
}

string IPPool::GetAvailIp() {
    string null_str;
    WriteLocker locker(m_lock);
    for (map<string, bool>::iterator it = m_ip_map.begin();
         it != m_ip_map.end(); ++it) {
        if (it->second) {
            it->second = false;
            return it->first;
        }
    }
    LOG4CPLUS_ERROR(logger, "No avail ip addr");
    return null_str;
}

bool IPPool::ReleaseIp(const string& ip) {
