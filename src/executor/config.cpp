/********************************
 FileName: executor/config.cpp
 Author:   WangMin
 Description: config for executor
*********************************/

#include "gflags/gflags.h"

DEFINE_int32(port, 9997, "executor port");
DEFINE_string(resource_scheduler_endpoint, "127.0.0.1:9998", "ResouceScheduler endpoint");
