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
