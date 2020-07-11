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

DECLARE_bool(debug);

/* task action handle*/
// start task
bool StartActionEvent::Handle() {
    TaskID id = GetID();
    if(FLAGS_debug) {
        LOG4CPLUS_DEBUG(logger, "Trigger event of start task action, job_id:" << id.job_id << ", task_id:" << id.task_id);
    }
    if (!TaskPoolI::Instance()->StartTaskByID(id)) {
        LOG4CPLUS_ERROR(logger, "Failed to start task, job_id:" << id.job_id << ", task_id:" << id.task_id);
        return false;
    }

    LOG4CPLUS_INFO(logger, "Handle event of start task action, job_id:" << id.job_id << ", task_id:" << id.task_id);
    return true;
}

// kill task
bool KillActionEvent::Handle() {
    TaskID id = GetID();
    if(FLAGS_debug) {
    LOG4CPLUS_DEBUG(logger, "Trigger event of kill task action, job_id:" << id.job_id << ", task_id:" << id.task_id);
    }
    if (!TaskPoolI::Instance()->KillTaskByID(id)) {
        LOG4CPLUS_ERROR(logger, "Failed to kill task, job_id:" << id.job_id << ", task_id:" << id.task_id);
        return false;
    }

    TaskPoolI::Instance()->Delete(id);
    LOG4CPLUS_INFO(logger, "Handle event of kill task action, job_id:" << id.job_id << ", task_id:" << id.task_id);
    return true;
}

//stop task TODO

bool StopActionEvent::Handle() {
    return true;
}

/* task state handle */
// task starting
bool StartingTaskEvent::Handle() {
    TaskID id = GetID();
    if(FLAGS_debug) {
        LOG4CPLUS_DEBUG(logger, "Trigger event of taskstarting state, job_id:" << id.job_id << ", task_id:" << id.task_id);
    }
    TaskPoolI::Instance()->GetTaskPtr(id)->TaskStarting();
    LOG4CPLUS_INFO(logger, "Handle event of taskstarting state, job_id:" << id.job_id << ", task_id:" << id.task_id);
    return true;
}

// task running
