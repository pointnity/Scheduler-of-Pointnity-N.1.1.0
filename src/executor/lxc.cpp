/********************************
 FileName: executor/lxc.cpp
 Version:  0.1
 Description: lxc(Linux Container), inherit from vm
*********************************/

#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
//#include <sys/unistd.h>
//#include <dirent.h>
#include <fcntl.h> // for func open
//#include <time.h>
//#include <signal.h>

#include <boost/algorithm/string.hpp>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "lxc/lxc.h"
#include "lxc/conf.h"

#include "common/clynn/string_utility.h"
#include "common/lxc/confile.h"
#include "executor/hdfs_wrapper.h"
#include "include/proxy.h"
#include "executor/system.h"
#include "executor/lxc.h"
#include "executor/task_entity_pool.h"
#include "executor/resource_manager.h"

using std::cout;
using std::endl;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using boost::trim;
using log4cplus::Logger;
using clynn::WriteLocker;
using clynn::ReadLocker;

DECLARE_string(lxc_dir);
DECLARE_string(lxc_template);
DECLARE_bool(lxc_create);
DECLARE_bool(lxc_relative_path);

static Logger logger = Logger::getInstance("executor");

static const double DEFAULT_CPU_SHARE = 1.0;

string LXC::m_conf_template = "";

/// @brief: public function
// virtual function, from VM
// virtual CreateEnv, include ..
int32_t LXC::Execute() {
    if (CreateVM() != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to create lxc, name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return -1;
    }

    if (InstallApp() != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to install app, lxc name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return -1;
    }

    if (LXC::StartApp() != 0){
        LOG4CPLUS_ERROR(logger, "Failed to start app, lxc name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return -1;	
    }

    return 0;

}

int32_t LXC::CreateVM() {
    if (CreateLXC() != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to create lxc, name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return -1;
    }
    return 0;
}

// install app from hdfs
int32_t LXC::InstallApp() {
    if (!HDFSMgrI::Instance()->CopyToLocalFile(GetTaskInfo().app_info.app_src_path, m_dir)) {
        LOG4CPLUS_ERROR(logger, "Failed to install app, from hdfs:" << GetTaskInfo().app_info.app_src_path  << ", to local fs:" << m_dir);
        return -1;
    }
    return 0;
}

// execute the task, run the app
int32_t LXC::StartApp() {
    if (ExecuteLXC() != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to execute lxc, name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return -1;
    }
    return 0;
}

bool LXC::Stop() {
    // 
    string cmd = "lxc-stop -n " + GetName();
    int32_t ret = system(cmd.c_str());
    ret = ret >> 8;
    if (ret != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to stop lxc, name:" << GetName());
        return false;
    }
    return true;
}

bool LXC::Kill() {
    string cmd_stop = "lxc-stop -n " + GetName();
    int32_t ret_stop = system(cmd_stop.c_str());
    ret_stop = ret_stop >> 8;
    if (ret_stop != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to stop lxc, name:" << GetName());
        return false;
    }
