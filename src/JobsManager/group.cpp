/********************************
FileName: JobsManager/group.cpp


Version: 0.2
Description: group: quota & queues
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"
#include "common/clynn/rpc.h"
#include "JobsManager/group.h"

using log4cplus::Logger;
using clynn::WriteLocker;
using clynn::ReadLocker;

static Logger logger = Logger::getInstance("JobsManager");

// gflag
DECLARE_string(resource_scheduler_endpoint);

// static data member
double Group::s_total_cpu = 1; // Prevention for 0
double Group::s_total_memory = 1;

Group::Group(const string& name) {
    Init(name);
}

void Group::Init(const string& name) {
    m_group_name = name;
}

string Group::GetGroupName() {
    return m_group_name;
}

// Add Job to Wait Queue
bool Group::AddJobToWaitQueue(const JobPtr& job, bool push_front) {
    JobQueueNum job_queue_num;
    if (!GetNewJobWaitQueueNum(job, job_queue_num)) {
        LOG4CPLUS_ERROR(logger, "No this priority.");
        return false;
    }

    if (!AddJobToQueueByQueueNum(job, job_queue_num, push_front)) {
        LOG4CPLUS_ERROR(logger, "No this queue num.");
        return false;
    }
    return true;
}

// Add Job to Wait Queue Bu Queue Num
bool Group::AddJobToQueueByQueueNum(const JobPtr& job, const JobQueueNum& num, bool push_front){
    switch (num) {
        case JOB_QUEUE_HIGH_WAIT:
            if (push_front) {
                WriteLocker locker(m_high_wait_job_queue_lock);
                m_high_wait_job_queue.push_front(job);
            } else {
                WriteLocker locker(m_high_wait_job_queue_lock);
                m_high_wait_job_queue.push_back(job);
                // TODO test
                printf("%s, High\n", GetGroupName().c_str());
            }
            return true;
        case JOB_QUEUE_ORDINARY_WAIT:
            if (push_front) {
                WriteLocker locker(m_ordinary_wait_job_queue_lock);
                m_ordinary_wait_job_queue.push_front(job);
            } else {
                WriteLocker locker(m_ordinary_wait_job_queue_lock);
                m_ordinary_wait_job_queue.push_back(job);
                printf("%s, Ordinary\n", GetGroupName().c_str());
            }
            return true;
        case JOB_QUEUE_LOW_WAIT:
            if (push_front) {
