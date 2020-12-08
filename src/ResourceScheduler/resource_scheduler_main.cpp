/********************************
 FileName: ResourceScheduler/resource_scheduler.cpp


 Version:  0.1
 Description: ResourceScheduler main
*********************************/
#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <gflags/gflags.h>

#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "ResourceScheduler/resource_scheduler_service.h"
#include "ResourceScheduler/dispatcher.h"


using std::string;
using std::cout;
using std::endl;
using std::auto_ptr;
