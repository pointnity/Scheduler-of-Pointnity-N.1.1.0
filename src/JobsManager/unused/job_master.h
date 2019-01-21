/********************************
 FileName: JobsManager/job_master.h
 
 
 Version:  0.1
 Description: master of navigating job, making resource request for job
*********************************/

#ifndef JOBS_MANAGER_JOB_MASTER_H
#define JOBS_MANAGER_JOB_MASTER_H

#include <list>
#include "JobsManager/job_match_data_type.h"
#include "JobsManager/job.h"
#include "JobsManager/job_matcher.h"

using std::list;

class JobMaster {
public:
    JobMaster(const JobPtr& job_ptr) : m_navigating_job(job_ptr) {}
    JobMaster() {}
    int32_t MakeMatch();
    int32_t MakeMatchOneTask(const TaskPtr& task_ptr);
    int32_t StartTasks();
