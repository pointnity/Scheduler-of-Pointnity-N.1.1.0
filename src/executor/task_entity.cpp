/********************************
 FileName: executor/task_entity.cpp
 Version:  0.1
 Description: task entity in executor, corresponds to task, corresponds to kvm/lxc
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include <iostream>
#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "include/classad_attr.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "executor/task_entity.h"
#include "executor/vm_pool.h"
#include "executor/ip_pool.h"
#include "executor/dispatcher.h"


using log4cplus::Logger;
using clynn::WriteLocker;
using clynn::ReadLocker;

static Logger logger = Logger::getInstance("executor");

DECLARE_string(jobs_manager_endpoint);
DECLARE_bool(jobs_manager_up);
DECLARE_bool(debug);

TaskEntity::TaskEntity(const string& task_info) {
    m_string_info = task_info;
    m_state = TaskEntityState::TASKENTITY_WAITING;
    m_percentage = 0;
}

bool TaskEntity::IsLegal() {
    // classad init, string task_info --> ClassAd *ad_ptr
    ClassAdParser parser;
    ClassAd* ad_ptr = parser.ParseClassAd(m_string_info);

    if (!ad_ptr) {
        LOG4CPLUS_ERROR(logger, "Failed to parse classad, ClassAd pointer is NULL."); 
        return false;
    }
    // task overview
    if (!ad_ptr->EvaluateAttrNumber(ATTR_JOB_ID, m_info.id.job_id)) {
        LOG4CPLUS_ERROR(logger, "Parse " << ATTR_JOB_ID << " error.");
        return false;
    }

    if (!ad_ptr->EvaluateAttrNumber(ATTR_TASK_ID, m_info.id.task_id)) {
        LOG4CPLUS_ERROR(logger, "Parse " << ATTR_TASK_ID << " error.");
    }

    int32_t type = -1;
    if (!ad_ptr->EvaluateAttrNumber(ATTR_VMTYPE, type)) {
        LOG4CPLUS_ERROR(logger, "Parse " << ATTR_VMTYPE << " error.");
        return false;
    }
    m_info.type = VMType::type(type);
    // printf("VMType: %d\n", m_info.type);

    if (!ad_ptr->EvaluateAttrBool(ATTR_IS_RUN, m_info.is_run)) {
        LOG4CPLUS_ERROR(logger, "Parse " << ATTR_IS_RUN << " error.");
        return false;
    }

    // seconds to min
    int32_t timeout;
    if (!ad_ptr->EvaluateAttrNumber(ATTR_TIMEOUT, timeout)) {
