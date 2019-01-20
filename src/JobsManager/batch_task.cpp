#include "include/classad_attr.h"
#include "JobsManager/batch_task.h"

using clynn::ReadLocker;
using clynn::WriteLocker;

/* void BatchTask::InitTaskInfo(TaskAdPtr ads, int32_t job_id,
                             int32_t task_id, int32_t submit_time) {

} */

/* bool BatchTask::SetTaskStartSuccess() {
    WriteLocker locker(m_lock);
    if(m_task_state != TASK_STARTING && 
       m_task_state != TASK_WAITING) {
       return false;
    }   
    m_task_state = TASK_RUNNING;
