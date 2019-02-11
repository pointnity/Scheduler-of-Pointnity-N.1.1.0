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

