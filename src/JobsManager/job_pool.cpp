/********************************
 FileName: JobsManager/job_pool.cpp


 Version:  0.1
 Description: pool of jobs, including map, list
*********************************/

#include "JobsManager/job_pool.h"

using clynn::ReadLocker;
using clynn::WriteLocker;
using std::make_pair;

bool JobPool::InsertIfAbsent(const JobPtr& job_ptr) {
    WriteLocker locker(m_map_lock);
