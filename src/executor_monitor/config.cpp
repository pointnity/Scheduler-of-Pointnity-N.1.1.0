/********************************
 FileName: executor_monitor/config.cpp
 Version:  0.1
 Description: config for executor_monitor
*********************************/

#include "gflags/gflags.h"

DEFINE_string(resource_scheduler_endpoint, "127.0.0.1:9998", "ResouceScheduler endpoint");
DEFINE_string(log_path, "../log/", "executor log path");
