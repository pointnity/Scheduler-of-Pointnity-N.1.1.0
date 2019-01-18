/********************************
 FileName: JobsManager/app_manager.cpp
 
 
 Version:  0.1
 Description: app maneger
*********************************/
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <iostream>
#include <string>

#include "JobsManager/app_manager.h"
#include "common/clynn/rpc.h"
#include "include/proxy.h"

using log4cplus::Logger;
