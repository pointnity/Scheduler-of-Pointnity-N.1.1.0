/********************************
 FileName: JobsManager/JobsManager.cpp


 Version:  0.1
 Description: JobsManager main
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
#include "JobsManager/group_pool.h"
#include "JobsManager/jobs_manager_service.h"
#include "JobsManager/dispatcher.h"

using std::string;
using std::cout;
using std::endl;
using std::auto_ptr;

using log4cplus::Logger;
using log4cplus::ConsoleAppender;
