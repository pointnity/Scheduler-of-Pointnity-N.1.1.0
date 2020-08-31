/********************************
 FileName: executor/task_entity.cpp
 Version:  0.1
 Description: task entity in executor, corresponds to task, corresponds to kvm/lxc
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include <iostream>
#include "common/clynn/rpc.h"
#include "executor/task_action.h"
#include "executor/task_entity_pool.h"
