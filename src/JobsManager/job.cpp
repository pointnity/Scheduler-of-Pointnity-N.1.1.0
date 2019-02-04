#include "JobsManager/job.h"
#include "JobsManager/job_num.h"
#include "JobsManager/task.h"
#include "include/classad_attr.h"
#include "common/classad/classad_complement.h"

using clynn::ReadLocker;
using clynn::WriteLocker;

Job::Job() {
    m_next_task_id = 0;
    m_job_id = 0;
    m_raw_priority = JOB_RAW_PRIO_ORDINARY;
    m_total_running_time = 0; 
    m_total_waiting_time = 0;
}

void Job::SetWaitTime() {
    m_wait_time = time(NULL);
}

void Job::SetRunTime() {
    m_run_time = time(NULL);
}

void Job::UpdateTimeByState(const TaskState& state){
    if (state == TASK_RUNNING) {
        m_total_running_time += (time(NULL) - m_run_time);
    } else if (state == TASK_WAITING){
