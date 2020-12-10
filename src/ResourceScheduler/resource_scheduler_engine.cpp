/********************************
 FileName: ResourceScheduler/resource_scheduler_engine.cpp
 
 
 Version:  0.1
 Description: resource scheduler engine
*********************************/

#include <sys/time.h>

#include <tr1/functional>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <algorithm>
#include <gflags/gflags.h>

#include <iostream>

#include "common/clynn/rpc.h"
#include "ResourceScheduler/resource_scheduler_engine.h"
#include "include/classad_attr.h"
#include "include/type.h"
#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"
#include "ResourceScheduler/dispatcher.h"


using log4cplus::Logger;
