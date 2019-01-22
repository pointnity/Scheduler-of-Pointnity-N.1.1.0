#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include "common/clynn/timer.h"
#include "common/clynn/rpc.h"
#include "common/classad/classad_complement.h"
#include "JobsManager/job_matcher.h"
#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"

DECLARE_string(resource_scheduler_endpoint);

using log4cplus::Logger;
using clynn::Timer;
