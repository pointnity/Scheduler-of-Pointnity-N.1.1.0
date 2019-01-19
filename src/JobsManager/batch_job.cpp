#include "JobsManager/batch_job.h"
#include "JobsManager/batch_task.h"

//Some of the following functions are locked when called

TaskPtr BatchJob::NewTask() const {
     return TaskPtr(new BatchTask());
}

bool BatchJob::HaveWaitingTasks() {
    for(list<TaskPtr>::const_iterator it = m_task_list.begin();
        it != m_task_list.end(); ++it) {
        if((*it)->GetTaskState() == TASK_WAITING) {
            return true;
        }
