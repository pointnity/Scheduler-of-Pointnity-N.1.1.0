/********************************
 FileName: jobs_manager/jobs_manager_service.cpp


 Version:  0.1
 Description: jobs_manager service
*********************************/
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include "JobsManager/jobs_manager_service.h"
#include "JobsManager/job_parser.h"
#include "JobsManager/task.h"
#include "JobsManager/event.h"
#include "JobsManager/dispatcher.h"
#include "JobsManager/job_pool.h"
#include "JobsManager/group_pool.h"

using log4cplus::Logger;

static Logger logger = Logger::getInstance("JobsManager");

void JobsManagerService::SubmitJob(SubmitJobResult& result, const string& job_xml) {
    JobParser job_parser;
    int32_t ret = job_parser.SubmitNewJob(job_xml, result.job_id); 
    result.error_num = ret;
}

void JobsManagerService::GetJobId(vector<int32_t>& job_id_list) {
    return JobPoolI::Instance()->GetJobIdList(job_id_list);
}

void JobsManagerService::GetTaskStateInfo(vector<TaskStateInfo>& task_state_info_list, int32_t job_id) {
    return JobPoolI::Instance()->GetTaskStateInfo(task_state_info_list, job_id);
}

bool JobsManagerService::TaskStarted(int32_t job_id, int32_t task_id) {
    if (job_id < 0 || task_id < 0) {
        return false;
    }
    // new TaskStartedEvent
    EventPtr event(new TaskStartedEvent(job_id, task_id));
    // Push event into Queue
    EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
    return true;
} 

bool JobsManagerService::TaskFinished(int32_t job_id, int32_t task_id) {
    if (job_id < 0 || task_id < 0) {
        return false;
    }
    EventPtr event(new TaskFinishedEvent(job_id, task_id));
    // Push event into Queue
    EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
    return true;
}

bool JobsManagerService::TaskFailed(int32_t job_id, int32_t task_id) {
    if (job_id < 0 || task_id < 0) {
        return false;
    }
    // new TaskFailedEvent
    EventPtr event(new TaskFailedEvent(job_id, task_id));
    // Push event into Queue
    EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
    return true;
}

bool JobsManagerService::TaskTimeout(int32_t job_id, int32_t task_id) {
    if (job_id < 0 || task_id < 0) {
        return false;
    }
    // new TaskFailedEvent
    EventPtr event(new TaskTimeoutEvent(job_id, task_id));
    // Push event into Queue
