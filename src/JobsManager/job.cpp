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
        m_total_waiting_time += (time(NULL) - m_wait_time);
    }
}

string Job::GetGroupName() {
    return m_group_name;
}

int32_t Job::GetRawPriority() {
    return m_raw_priority;
}

int32_t Job::GetSchedModel() {
    return m_sched_model;
}

int32_t Job::GetState() {
    return m_state;
}

void Job::SetState(int state) {
    m_state = state;
}

int32_t Job::GetJobId(){
    return m_job_id;
}

double Job::GetNeedCpu() {
    return m_need_cpu;
}

int32_t Job::GetNeedMemory() {
    return m_need_memory;
}

void Job::Init(const ClassAdPtr& classad_ptr, bool constraints_among_tasks) {
    WriteLocker locker(m_lock);
    m_job_classad_ptr = ClassAdPtr(new ClassAd(*classad_ptr));
    m_job_id = JobNumI::Instance()->GetNewJobId();
    m_job_classad_ptr->InsertAttr(ATTR_JOB_ID, m_job_id);
    m_job_classad_ptr->EvaluateAttrString(ATTR_GROUP, m_group_name);
    m_job_classad_ptr->EvaluateAttrNumber(ATTR_PRIO, m_raw_priority);
    if (m_raw_priority > 3)
        m_raw_priority = 2;
    m_job_classad_ptr->EvaluateAttrNumber(ATTR_SCHED_MODEL, m_sched_model);
    m_job_classad_ptr->EvaluateAttrNumber(ATTR_NEED_CPU, m_need_cpu);
    m_job_classad_ptr->EvaluateAttrNumber(ATTR_NEED_MEMORY, m_need_memory);
    m_constraints_among_tasks = constraints_among_tasks;
}

void Job::InitTasks(const list<TaskAdPtr>& task_ad_list) {
    WriteLocker locker(m_lock);
    for (list<TaskAdPtr>::const_iterator it = task_ad_list.begin();
         it != task_ad_list.end(); ++it)
    {
            //This is a direct batchtask.
            //Make a press TASKG factory class TODO
            //TaskPtr task_ptr(new BatchTask());
            TaskPtr task_ptr = NewTask();
            task_ptr->InitTaskInfo(*it, m_job_id, m_next_task_id, m_submit_time);
            m_next_task_id++;
