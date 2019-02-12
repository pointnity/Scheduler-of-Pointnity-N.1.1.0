/********************************
 FileName: JobsManager/job_scheduler.h


 Version:  0.2
 Description: scheduler of navigating job, making resource request for job
*********************************/

#ifndef JOBS_MANAGER_JOB_SCHEDULER_H
#define JOBS_MANAGER_JOB_SCHEDULER_H

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

#include "JobsManager/job.h"
#include "JobsManager/task.h"

// used in child class
#include "common/clynn/string_utility.h"
#include "JobsManager/job_enum.h"
#include "JobsManager/job_pool.h"
