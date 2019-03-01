/********************************
 FileName: ResourceScheduler/resource_scheduler_service.cpp


 Version:  0.1
 Description: resource scheduler service
*********************************/


#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "include/proxy.h"
#include "common/clynn/rpc.h"

#include "ResourceScheduler/resource_scheduler_service.h"
#include "ResourceScheduler/resource_scheduler_engine.h"
#include "ResourceScheduler/match_maker.h"
#include "ResourceScheduler/dispatcher.h"

#include <iostream>
#include <sstream>
#include <string>
