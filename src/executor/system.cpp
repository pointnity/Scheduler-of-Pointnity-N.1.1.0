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
