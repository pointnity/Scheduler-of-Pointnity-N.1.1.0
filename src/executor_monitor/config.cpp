/********************************
 FileName: executor_monitor/config.cpp
 Version:  0.1
 Description: config for executor_monitor
*********************************/

#include "gflags/gflags.h"

DEFINE_string(resource_scheduler_endpoint, "127.0.0.1:9998", "ResouceScheduler endpoint");
DEFINE_string(log_path, "../log/", "executor log path");
DEFINE_string(hdfs_host, "localhost", "hdfs local host name, uname -n");
DEFINE_int32(hdfs_port, 9000, "hdfs default port");
