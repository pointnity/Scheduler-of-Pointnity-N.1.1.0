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
    // static init
    /* if (m_max_times = -1)
         m_max_times = FLAGS_max_restart_times;*/
    // hard constraint   
    m_taskad_hard_constraint = ads->taskad_hard_constraint;
    m_job_id = job_id;
    m_taskad_hard_constraint->InsertAttr(ATTR_JOB_ID, job_id);
    // TODO 
    // m_task_id = task_id;
    // m_taskad_hard_constraint->InsertAttr(ATTR_TASK_ID, task_id);
    m_taskad_hard_constraint->EvaluateAttrNumber(ATTR_TASK_ID, m_task_id);
    m_taskad_hard_constraint->EvaluateAttrString(ATTR_GROUP, m_group_name);
    m_taskad_hard_constraint->EvaluateAttrNumber(ATTR_PRIO, m_raw_priority);
    m_taskad_hard_constraint->EvaluateAttrNumber(ATTR_SCHED_MODEL, m_sched_model);
    m_taskad_hard_constraint->EvaluateAttrNumber(ATTR_NEED_CPU, m_need_cpu);
    m_taskad_hard_constraint->EvaluateAttrNumber(ATTR_NEED_MEMORY, m_need_memory);
    m_taskad_hard_constraint->EvaluateAttrNumber(ATTR_NEED_MEMORY, m_timeout);
    m_timeout = m_timeout * 60;

    m_restart_times = 0;
    m_failed_times = 0;
    m_timeout_times = 0;
    m_missed_times = 0;
