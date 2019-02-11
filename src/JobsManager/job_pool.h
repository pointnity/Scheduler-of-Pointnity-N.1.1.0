/********************************
 FileName: JobsManager/job_pool.h


 Version:  0.1
 Description: pool of jobs, including map, list
*********************************/

#ifndef JOB_POOL_H
#define JOB_POOL_H

#include <map>
#include "common/clynn/rwlock.h"
#include "common/clynn/singleton.h"
#include "include/proxy.h"
#include "JobsManager/job.h"

using std::map;
