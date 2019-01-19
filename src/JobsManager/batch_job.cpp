#include "JobsManager/batch_job.h"
#include "JobsManager/batch_task.h"

//Some of the following functions are locked when called

TaskPtr BatchJob::NewTask() const {
     return TaskPtr(new BatchTask());
}

bool BatchJob::HaveWaitingTasks() {
