/********************************
 FileName: JobsManager/task.cpp


 Version:  0.1
 Description: task, include ClassAd m_taskad_hard_constraint and list<ClassAd> m_soft_constraint_list
*********************************/

#include "JobsManager/task.h"

using clynn::ReadLocker;
using clynn::WriteLocker;

TaskStatus Task::GetTaskStatus() {
    ReadLocker locker(lock);
    return m_task_status;
}

void Task::SetTaskStatus(int32_t status) {
    WriteLocker locker(lock);
    m_task_status = TaskStatus(status);
}

int Task::GetTaskId() {
    return m_task_id;
}

int Task::GetJobId() {
    return m_job_id;
