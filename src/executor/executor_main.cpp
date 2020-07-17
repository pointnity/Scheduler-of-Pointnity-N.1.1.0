/********************************
 FileName: executor/executor.cpp
 Version:  0.1
 Description: executor main
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
#include "executor/system.h"
#include "executor/service.h"
#include "executor/dispatcher.h"
#include "executor/resource_manager.h"
#include "executor/hdfs_wrapper.h"
#include "executor/ip_pool.h"
#include "executor/executor_register.h"


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
DECLARE_int32(port);
DECLARE_string(collector_endpoint);
DECLARE_string(scheduler_endpoint);
/*DECLARE_string(interface);
DECLARE_string(img_dir);*/
DECLARE_string(log_path);
DECLARE_string(libvirt_dir);
DECLARE_string(xml_template);
DECLARE_string(lxc_dir);
DECLARE_string(lxc_template);
DECLARE_string(hdfs_host);

//extern void* TaskProcessor(void* unused);
extern void* VMProcessor(void* unused);
extern void* HeartbeatProcessor(void* unused);

// executor
int ExecutorEntity(int argc, char **argv) {
    // config file
    if (argc > 1)
        google::ParseCommandLineFlags(&argc, &argv, true);
    else
        google::ReadFromFlagsFile("../conf/executor.conf", argv[0], true);

    // get time
    /* char time_c[64] = {0};
    System::GetCurrentTime(time_c, sizeof(time_c)-1);
    string time_str = time_c;*/
