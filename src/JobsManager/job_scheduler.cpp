/********************************
 FileName: JobsManager/job_scheduler.cpp


 Version:  0.2
 Description: scheduler of navigating job, making resource request for job
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "common/clynn/timer.h"
#include "common/clynn/rpc.h"
#include "common/classad/classad_complement.h"
#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"

#include "JobsManager/job_scheduler.h"

DECLARE_string(resource_scheduler_endpoint);

using log4cplus::Logger;
using clynn::Timer;

static Logger logger = Logger::getInstance("JobsManager");

int32_t JobScheduler::SendRequest(const string& classad, string& match_result) {
    LOG4CPLUS_INFO(logger, "SendRequest " << classad);
