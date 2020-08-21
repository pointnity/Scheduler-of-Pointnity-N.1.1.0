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

using log4cplus::Logger;

static Logger logger = Logger::getInstance("executor");

DECLARE_bool(debug);

// test, hello world
int32_t ExecutorService::Helloworld() {
    printf("Hello world\n");
    return 0;
}

//RS
bool ExecutorService::Exit() {
    // new KillActionEvent
    EventPtr event(new ExitExecutorEvent());
    // Push event into Queue
    EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
    return true;
}
// task
bool ExecutorService::StartTask(const string& info) {
    TaskPtr ptr(new TaskEntity(info));
    if (false == ptr->IsLegal()) {
        LOG4CPLUS_ERROR(logger, "Failed to initialize TaskEntity");
        return false;
    }
    if (false == TaskPoolI::Instance()->InsertIfAbsent(ptr)) {
        LOG4CPLUS_ERROR(logger, "The task had exist in the executor, job_id:" << ptr->GetID().job_id << ", task_id:" << ptr->GetID().task_id);
        TaskPoolI::Instance()->PrintAll();
        return false;
    }

    //get task id
    TaskID id = ptr->GetID();
    // new startActionEvent
    EventPtr event(new StartActionEvent(id));
    // Push event into Queue
    EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);

    if (FLAGS_debug)
        TaskPoolI::Instance()->PrintAll();
    return true;
    
}

bool ExecutorService::KillTask(const int32_t job_id, const int32_t task_id) {
    if (job_id < 0 || task_id < 0) {
        LOG4CPLUS_ERROR(logger, "TaskID is illegal, job_id:" << job_id << ", task_id:" << task_id);
        return false;
    }
    TaskID id;
    id.job_id = job_id;
    id.task_id = task_id;
    // new KillActionEvent
    EventPtr event(new KillActionEvent(id));
    // Push event into Queue
    EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
    return true;
}

bool ExecutorService::KillTaskForFT(const int32_t job_id, const int32_t task_id) {
    if (job_id < 0 || task_id < 0) {
        LOG4CPLUS_ERROR(logger, "TaskID is illegal, job_id:" << job_id << ", task_id:" << task_id);
        return false;
    }
    TaskID id;
    id.job_id = job_id;
    id.task_id = task_id;
    // new KillActionEvent
    EventPtr event(new KillActionEvent(id));
