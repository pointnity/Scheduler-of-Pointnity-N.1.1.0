/********************************
 FileName: JobsManager/task.cpp


 Version:  0.1
 Description: task, include ClassAd m_taskad_hard_constraint and list<ClassAd> m_soft_constraint_list
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "common/clynn/rpc.h"
#include "include/proxy.h"
#include "include/classad_attr.h"
#include "JobsManager/task.h"
#include "JobsManager/group_pool.h"
#include "JobsManager/job_master.h"

using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("JobsManager");

DECLARE_int32(max_restart_times);

int32_t Task::s_max_times = 3;

void Task::InitTaskInfo(TaskAdPtr ads, int32_t job_id, int32_t 
                             task_id, int32_t submit_time) {
