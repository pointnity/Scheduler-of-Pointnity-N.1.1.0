/********************************
 FileName: JobsManager/job_selector.cpp
 
 
 Version:  0.1
 Description: selector one job from Queues, then make resource request
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "JobsManager/job_selector.h"
#include "JobsManager/group.h"
#include "JobsManager/group_pool.h"

using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("JobsManager");
