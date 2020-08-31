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
#include "executor/task_entity.h"
#include "executor/dispatcher.h"


using log4cplus::Logger;
using clynn::WriteLocker;
using clynn::ReadLocker;

static Logger logger = Logger::getInstance("executor");

DECLARE_string(jobs_manager_endpoint);
DECLARE_bool(jobs_manager_up);
DECLARE_bool(debug);

void TaskAction::TaskRunning(TaskID id) {
    TaskPtr task_ptr = TaskPoolI::Instance()->GetTaskPtr(id);
    TaskEntityState::type m_state = task_ptr->GetState();
    //update task state to JM
