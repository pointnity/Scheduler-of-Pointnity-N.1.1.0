/********************************
 FileName: executor/resource_manager.cpp
 Version:  0.1
 Description: resource manager of the machine(execute node)
*********************************/

#include <stdlib.h>
#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "common/classad/classad_complement.h"
#include "include/classad_attr.h"
#include "include/type.h"
#include "executor/system.h"
#include "executor/vm_pool.h"
#include "executor/image_manager.h"
#include "executor/resource_manager.h"

using std::cout;
using std::endl;
using std::stringstream;
using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

DECLARE_int32(port);
DECLARE_string(resource_scheduler_endpoint);
DECLARE_string(interface);
DECLARE_string(if_bridge);
DECLARE_string(lynn_version);


static Logger logger = Logger::getInstance("executor");

// init, set static info 
// TODO
bool ResourceManager::Init() {
    /// @brief: set private info
    // ip
    m_ip = System::GetIP(FLAGS_interface.c_str());
    m_bridge_ip = System::GetIP(FLAGS_if_bridge.c_str());
    m_port = FLAGS_port;

    // machine & arch
    m_name = m_ip;
    m_machine_type = "A";
    m_shelf_number = -1;
    m_arch = "Intel";
    m_os = System::GetOSVersion();

    m_total_cpu = System::GetCpuNum();
    m_total_memory = System::GetTotalMemory(); 
    m_total_disk = System::GetTotalDisk();
