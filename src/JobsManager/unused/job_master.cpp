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
#include "common/clynn/string_utility.h"
#include "common/classad/classad_complement.h"

#include "JobsManager/job_enum.h"
#include "JobsManager/job_master.h"
#include "JobsManager/job_pool.h"
#include "JobsManager/group.h"
#include "JobsManager/group_pool.h"
#include "JobsManager/job_match_data_type.h"
#include "JobsManager/event.h"
#include "JobsManager/dispatcher.h"

using clynn::ReadLocker;
using clynn::WriteLocker;
using log4cplus::Logger;

static Logger logger = Logger::getInstance("JobsManager");

int32_t JobMaster::MakeMatch() {
    printf("Making match.\n");

    if (NULL == m_navigating_job) { 
        // Error code TODO
        return -1;
    }

    int32_t rc;
    int32_t sched_model = m_navigating_job->GetSchedModel();
 
    if (WIDE_DISTRIBUTION == sched_model) {
        rc = MakeMatchWideDistribution();
    } else {
        if (false == m_navigating_job->GetConstraintsAmongTasks()) {
            rc = MakeMatchAsTasks();
        } else {
            rc = MakeMatchAsWhole();
        }
    }

    return rc;
}

int32_t JobMaster::MakeMatchOneTask(const TaskPtr& task_ptr) {
    printf("Making match One Task.\n");

    int32_t rc;
    int32_t sched_model = task_ptr->GetSchedModel();


     if (WIDE_DISTRIBUTION == sched_model) {
        rc = MakeMatchOneTaskWD(task_ptr);
    } else {
        rc = MakeMatchOneTaskDefault(task_ptr);
    }

    return rc;
}

int32_t JobMaster::StartTasks() {
    for (list<TaskMatchInfo>::iterator it = m_match_list.begin();
        it != m_match_list.end(); ++it)
    {
        EventPtr event(new StartTaskEvent(it->job_id, it->task_id, it->es_address, it->taskad_hard_constraint));
        // Push event into Queue
        EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);

        // state
