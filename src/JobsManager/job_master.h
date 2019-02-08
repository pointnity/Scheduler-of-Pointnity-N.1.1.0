/********************************
 FileName: JobsManager/job_master.h


 Version:  0.1
 Description: master of navigating job, making resource request for job
*********************************/

#ifndef JOBS_MANAGER_JOB_MASTER_H
#define JOBS_MANAGER_JOB_MASTER_H

#include <list>
#include "JobsManager/job.h"
#include "JobsManager/job_scheduler.h"
#include "JobsManager/default_scheduler.h"
#include "JobsManager/wd_scheduler.h"

using std::list;

class JobMaster {
public:
    JobMaster(const JobPtr& job_ptr);
    // JobMaster();
    int32_t Schedule();
   // int32_t ScheduleOneTask(const TaskPtr& task_ptr);

/*     int32_t MakeMatch();
