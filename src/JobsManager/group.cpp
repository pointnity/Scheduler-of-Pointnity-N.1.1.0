/********************************
FileName: JobsManager/group.cpp


Version: 0.2
Description: group: quota & queues
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"
#include "common/clynn/rpc.h"
#include "JobsManager/group.h"

using log4cplus::Logger;
using clynn::WriteLocker;
using clynn::ReadLocker;

static Logger logger = Logger::getInstance("JobsManager");

// gflag
DECLARE_string(resource_scheduler_endpoint);

// static data member
double Group::s_total_cpu = 1; // Prevention for 0
double Group::s_total_memory = 1;

Group::Group(const string& name) {
    Init(name);
}

void Group::Init(const string& name) {
    m_group_name = name;
