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
    if (FindById(job_ptr->GetJobId()))
        return false;
    Insert(job_ptr);
    return true;    
}

JobPtr JobPool::GetJobPtr(int32_t job_id) {
    ReadLocker locker(m_map_lock);
    map<int, JobPtr>::iterator it = m_id_map.find(job_id);
    if (it != m_id_map.end()) {
        return it->second;
    }
    return JobPtr();
}

bool JobPool::IsExist(int32_t job_id) {
    ReadLocker locker(m_map_lock);
