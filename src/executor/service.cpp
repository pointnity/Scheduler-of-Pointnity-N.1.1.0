/********************************
 FileName: executor/service.cpp
 Version:  0.1
 Description: executor service
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include <iostream>
#include "include/type.h"
#include "executor/task_entity_pool.h"
#include "executor/vm_pool.h"
#include "executor/dispatcher.h"
#include "executor/service.h"
#include "executor/image_manager.h"
