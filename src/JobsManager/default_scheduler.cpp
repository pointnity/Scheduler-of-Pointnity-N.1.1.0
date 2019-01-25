/********************************
 FileName: JobsManager/default_scheduler.cpp


 Version:  0.2
 Description: Default Scheduler, inherit from JobScheduler
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "common/clynn/timer.h"
#include "common/clynn/rpc.h"
#include "common/classad/classad_complement.h"
#include "include/classad_attr.h"

#include "JobsManager/default_scheduler.h"

DECLARE_string(resource_scheduler_endpoint);

using log4cplus::Logger;
using clynn::Timer;

static Logger logger = Logger::getInstance("JobsManager");

int32_t DefaultScheduler::ScheduleOneJob(JobPtr& job_ptr) {
