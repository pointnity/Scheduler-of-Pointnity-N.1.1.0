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
	    sscanf(line + 5, "%llu %llu %llu %llu %llu %llu %llu",
                    &cpu_user, &cpu_nice, &cpu_sys, &cpu_idle,
                    &cpu_iowait, &cpu_hardirq, &cpu_softirq);
            total = cpu_user + cpu_nice + cpu_sys +
                   cpu_iowait + cpu_hardirq + cpu_softirq + cpu_idle;
            break;
        }
    }

    // close file
    fclose(fp);
    return total;
}

// @return: cpu usage
double System::GetCpuUsage() {
    FILE* fp = fopen("/proc/stat", "r");
    if (!fp)
        return -1.0;

    char line[8192];
    // previous cpu time 
    static uint64_t prev_used = 0;
    static uint64_t prev_total = 0;
    static bool first = true;

    // cpu time now
    uint64_t cpu_user = 0;
    uint64_t cpu_nice = 0;
    uint64_t cpu_sys = 0;
    uint64_t cpu_idle = 0;
    uint64_t cpu_iowait = 0;
    uint64_t cpu_hardirq = 0;
    uint64_t cpu_softirq = 0;
    uint64_t used = 0;
    uint64_t total = 0;

    while (fgets(line, 8192, fp) != NULL) {
        if (!strncmp(line, "cpu ", 4)) {
            //sscanf(line + 5, "%"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64"",
	    sscanf(line + 5, "%llu %llu %llu %llu %llu %llu %llu",
                   &cpu_user, &cpu_nice, &cpu_sys, &cpu_idle,
                   &cpu_iowait, &cpu_hardirq, &cpu_softirq);
            used = cpu_user + cpu_nice + cpu_sys +
                   cpu_iowait + cpu_hardirq + cpu_softirq;
            total = used + cpu_idle;
            break;
        }
    }

    if (first) {
        first = false;
        prev_used = used;
        prev_total = total;
        fclose(fp);
        return 0.0;
    }

    // avoid 0
    if (total == prev_total) {
        total = prev_total + 1;
    }
                       / static_cast<double>(total - prev_total);
    prev_used = used;
    prev_total = total;

    // close file
    fclose(fp);
    return cpu_usage;
}

/// @brief: Memory
// @return: total physical memory, size(MB)
int32_t System::GetTotalMemory() {
    // fs /proc
    FILE* fp = fopen("/proc/meminfo", "r");
    if (!fp)
        return -1;

    int32_t total = 0;
    char buf[1024];
    // get memory info
    while (fgets(buf, sizeof(buf)-1, fp)) {
        if (strncmp(buf, "MemTotal:", 9) != 0)
            continue;
        char* b = strstr(buf, "MemTotal:");
        sscanf(b, "MemTotal: %d", &total);
    }

    // close file
    fclose(fp);
    total /= 1024;
    return total;
}    
  
// @return: free physical memoryi, size(MB)
int32_t System::GetPhysicalMemory() {
   FILE* fp = fopen("/proc/meminfo", "r");
       return -1;

   int32_t free = 0;
   int32_t buffer = 0;
   int32_t cache = 0;
   char buf[1024];
   while (fgets(buf, sizeof(buf)-1, fp)) {
       if (0 == strncmp(buf, "MemFree:", 8)) {
           char* b = strstr(buf, "MemFree: ");
           sscanf(b, "MemFree: %d", &free);
           continue;
       } else if (0 == strncmp(buf, "Buffers:", 8)) {
           char* b = strstr(buf, "Buffers: ");
           sscanf(b, "Buffers: %d", &buffer);
           continue;
       } else if (0 == strncmp(buf, "Cached:", 7)) {
           char* b = strstr(buf, "Cached: ");
           sscanf(b, "Cached: %d", &cache);
           break;
       }
   }

   // close file
   fclose(fp);
   return (free + buffer + cache) / 1024;
}

// @return: used memory size(MB)
int32_t System::GetUsedMemory() {
    int32_t total = GetTotalMemory();
    int32_t free = GetPhysicalMemory();

    if (total == -1 || free == -1 || free > total)
        return -1;
    return total - free;
}

// @return usage of memory
double System::GetMemoryUsage() {
    int32_t total = GetTotalMemory();
    int32_t used = GetUsedMemory();

    if (total == -1 || used == -1 || used > total)
        return -1;
    return (double)used / total;
}

// @return: return SwapTotal memory(size:MB) if success, or return -1
int32_t System::GetSwapTotalMemory() {
    // fs /proc
    FILE* fp = fopen("/proc/meminfo", "r");
    if (!fp)
        return -1;
    char buf[256] = {0};
    // get SwapTotal from /proc/meminfo
    while (fgets(buf, sizeof(buf) - 1, fp)) {
        if (0 == strncmp(buf, "SwapTotal", 9)) {
            if (sscanf(buf, "SwapTotal: %d", &swap_total) < 1) {
