/********************************
 FileName: executor_monitor/checker.cpp
 Version:  0.1
 Description: checker
*********************************/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <iostream>
#include <fstream>
#include <string>

#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "executor_monitor/checker.h"
#include "executor_monitor/hdfs_wrapper.h"

DECLARE_string(resource_scheduler_endpoint);
DECLARE_string(lynn_version);
DECLARE_string(executor_hdfs_path);


using log4cplus::Logger;
using namespace std;

static Logger logger = Logger::getInstance("executor_monitor");

bool Checker::CheckVersion() {
    // check executor version
    string new_lynn_version;
