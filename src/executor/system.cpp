/********************************
 FileName: executor/system.h
 Version:  0.1
 Description: get the physical resource info of the machine
*********************************/

#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/statfs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <time.h>
#include <sys/param.h>
#include <dirent.h>

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include "executor/system.h"

using boost::trim;

#define __STDC_FORMAT_MACROS
#include <inttypes.h> // for scanf uint64_t

/// @brief: Load
// @return: return avg load in 1 minute if success, or return -1
double System::GetLoadAvginOne() {
    // fs /proc
    FILE* fp = fopen("/proc/loadavg", "r");
    if (!fp)
        return -1.0;

    // get info from /proc/loadavg 
    double avg_1, avg_5, avg_15;
    fscanf(fp, "%lf %lf %lf", &avg_1, &avg_5, &avg_15);

    // close file
    fclose(fp);
    return avg_1;
}

// @return: return avg load in 5 minutes if success, or return -1
double System::GetLoadAvginFive() {
    // fs /proc
    FILE* fp = fopen("/proc/loadavg", "r");
    if (!fp)
        return -1.0;

    // get info from /proc/loadavg 
    double avg_1, avg_5, avg_15;
    fscanf(fp, "%lf %lf %lf", &avg_1, &avg_5, &avg_15);

    // close file
    fclose(fp);
    return avg_5;
}

// @return: return avg load in 15 minutes if success, or return -1
double System::GetLoadAvginFifteen() {
    // fs /proc
    FILE* fp = fopen("/proc/loadavg", "r");
    if (!fp)
        return -1.0;

    // get infoi from /proc/loadavg 
    double avg_1, avg_5, avg_15;
    fscanf(fp, "%lf %lf %lf", &avg_1, &avg_5, &avg_15);

    // close file
    fclose(fp);
    return avg_15;
}

/// @brief: CPU
// @return: logic cpu numbers
int32_t System::GetCpuNum() {
    // fs /proc
    FILE* fp = fopen("/proc/cpuinfo", "r");
    if (!fp)
        return 1;

    int32_t cpu_num = 0;
    char buf[256] = {0};
    // read each line, count cpu number as line number
    while (fgets(buf, sizeof(buf)-1, fp)) {
        if (strncmp(buf, "processor", 9) == 0) {
            cpu_num++;
        }
    }

    // close file
    fclose(fp);
    return cpu_num ? cpu_num : 1;
}

// @return: cpu time
uint64_t System::GetCpuTime() {
    // fs /porc
    FILE* fp = fopen("/proc/stat", "r");
    if (!fp)
         return 1;

    uint64_t cpu_user = 0;
    uint64_t cpu_nice = 0;
    uint64_t cpu_sys = 0;
    uint64_t cpu_idle = 0;
    uint64_t cpu_iowait = 0;
    uint64_t cpu_hardirq = 0;
    uint64_t cpu_softirq = 0;
    uint64_t total = 0;
    char line[8192];
    // get cpu time
    while (fgets(line, 8192, fp) != NULL) {
        if (!strncmp(line, "cpu ", 4)) {
            //sscanf(line + 5, "%"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64"",
