/********************************
FileName: JobsManager/group.cpp


Version: 0.2
Description: group: quota & queues
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"
#include "common/clynn/rpc.h"
#include "JobsManager/group.h"
