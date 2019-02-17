/********************************
FileName: JobsManager/wd_scheduler.cpp


 Version:  0.2
 Description: wide distribution Scheduler, inherit from JobScheduler
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "common/clynn/timer.h"
#include "common/clynn/rpc.h"
#include "common/classad/classad_complement.h"
#include "include/classad_attr.h"

#include "JobsManager/wd_scheduler.h"

DECLARE_string(resource_scheduler_endpoint);

using log4cplus::Logger;
using clynn::Timer;

static Logger logger = Logger::getInstance("JobsManager");

int32_t WDScheduler::ScheduleOneJob(JobPtr& job_ptr) {
    printf("WideDistribution\n");

    bool has_success = false;
    bool has_no_success = false;

    list<TaskPtr> task_list = job_ptr->GetTaskList();
    for (list<TaskPtr>::const_iterator it = task_list.begin();
        it != task_list.end(); ++it)
    {
        // only schedule waiting task
       if((*it)->GetTaskState() != TASK_WAITING) {
            continue;
        }

        if (ScheduleOneTask(*it) != 0) {
            has_no_success = true; // has task no success
        } else {
            has_success = true; // has task success 
        }
    }

    if (!has_no_success) {
        // all tasks success
        job_ptr->SetState(JOB_RUNNING);
        return 0;
    } else if (has_success) {
        // partly tasks success
        job_ptr->SetState(JOB_SCHEDULING);
