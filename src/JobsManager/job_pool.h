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
using std::list;
using std::pair;
using clynn::RWLock;

class JobPool {
public:
    bool InsertIfAbsent(const JobPtr& job_ptr);
    JobPtr GetJobPtr(int32_t job_id);
    bool IsExist(int32_t job_id);

    void HistoryJobListPushBack(const JobPtr& job_ptr);
