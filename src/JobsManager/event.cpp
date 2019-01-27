/********************************
 FileName: JobsManager/event.cpp


 Version:  0.1
 Description: event, and its handler
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "JobsManager/event.h"
#include "JobsManager/image_manager.h"
#include "JobsManager/app_manager.h"
#include "JobsManager/job_pool.h"


using log4cplus::Logger;

static Logger logger = Logger::getInstance("JobsManager");

