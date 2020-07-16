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
