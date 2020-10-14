/********************************
 FileName: executor_monitor/main.cpp
 Version:  0.1
 Description: executor_monitor main
*********************************/

#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <gflags/gflags.h>

#include "common/clynn/rpc.h"
#include "executor_monitor/hdfs_wrapper.h"
#include "executor_monitor/checker.h"


using std::string;
using std::cout;
using std::endl;
using std::auto_ptr;

using log4cplus::Logger;
using log4cplus::ConsoleAppender;
using log4cplus::FileAppender;
using log4cplus::Appender;
using log4cplus::Layout;
using log4cplus::PatternLayout;
using log4cplus::helpers::SharedObjectPtr;

// gflag, config for executor
DECLARE_string(log_path);
DECLARE_string(hdfs_host);
extern void* ExecutorMonitorProcessor(void* unused);

// executor
int ExecutorMonitorEntity(int argc, char **argv) {
    // config file
