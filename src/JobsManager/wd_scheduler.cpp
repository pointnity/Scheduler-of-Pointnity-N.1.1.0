/********************************
FileName: JobsManager/wd_scheduler.cpp


 Version:  0.2
 Description: wide distribution Scheduler, inherit from JobScheduler
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "common/clynn/timer.h"
#include "common/clynn/rpc.h"
#include "common/classad/classad_complement.h"
