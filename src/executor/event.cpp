/********************************
 FileName: executor/event.cpp
 Version:  0.1 & 0.2
 Description: event, and its handler
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "executor/event.h"
#include "executor/task_entity_pool.h"
#include "executor/task_action.h"
#include "executor/vm_pool.h"
#include "executor/image_manager.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("executor");
