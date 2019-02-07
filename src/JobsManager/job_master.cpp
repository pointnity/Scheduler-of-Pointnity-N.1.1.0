/********************************
 FileName: JobsManager/job_master.cpp


 Version:  0.1
 Description: master of navigating job, making resource request for job
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "include/proxy.h"
#include "include/classad_attr.h"
#include "common/clynn/rpc.h"
#include "common/clynn/rwlock.h"
#include "common/clynn/string_utility.h"
#include "common/classad/classad_complement.h"

#include "JobsManager/job_enum.h"
#include "JobsManager/job_master.h"
#include "JobsManager/job_pool.h"
#include "JobsManager/group.h"
