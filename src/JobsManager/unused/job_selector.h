/********************************
 FileName: JobsManager/job_selector.h
 
 
 Version:  0.1
 Description: selector one job from Queues, then make resource request
*********************************/

#ifndef JOBS_MANAGER_JOB_SELECTOR_H
#define JOBS_MANAGER_JOB_SELECTOR_H

#include <set>
#include "JobsManager/job_enum.h"
#include "JobsManager/job_master.h"

using std::set;

class JobSelector {
public
    bool SelectJob();    
private:
    // JobMaster m_job_master;
};

