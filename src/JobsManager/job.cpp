#include "JobsManager/job.h"
#include "JobsManager/job_num.h"
#include "JobsManager/task.h"
#include "include/classad_attr.h"
#include "common/classad/classad_complement.h"

using clynn::ReadLocker;
using clynn::WriteLocker;

Job::Job() {
    m_next_task_id = 0;
