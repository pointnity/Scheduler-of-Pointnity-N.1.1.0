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
    m_avail_cpu = m_total_cpu;
    m_avail_memory = m_total_memory;
    m_avail_disk = m_total_disk - System::GetUsedDisk();

    m_band_width = System::GetBandWidth(FLAGS_interface.c_str());
    m_nic_type = System::GetNICType(FLAGS_interface.c_str());

    /// @brief: get info, send info to collector
    string machine_info = GetMachineInfo();
    // TODO
    cout << machine_info << endl; 

     
    // VMPool Init check libvirt dir and lxc dir
    if (!VMPoolI::Instance()->Init()) {
        LOG4CPLUS_ERROR(logger, "error in VMPool Init.");
        return false;
    }
    return true;
}

string ResourceManager::GetMachineInfo() {
    ReadLocker lock(m_lock);

    // init classad
    ClassAd ad;
    ad.InsertAttr(ATTR_Machine, m_name);
    ad.InsertAttr(ATTR_MachineType, m_machine_type);
    ad.InsertAttr(ATTR_Shelf, m_shelf_number);
    ad.InsertAttr(ATTR_Machine_IP, m_ip);
    ad.InsertAttr(ATTR_Port, m_port);
    ad.InsertAttr(ATTR_Arch, m_arch);
    ad.InsertAttr(ATTR_OpSys, m_os);
    ad.InsertAttr(ATTR_TotalCPUNum, m_total_cpu);
    ad.InsertAttr(ATTR_TotalMemory, m_total_memory);
    ad.InsertAttr(ATTR_TotalDisk, m_total_disk);
    ad.InsertAttr(ATTR_BandWidth, m_band_width);
    ad.InsertAttr(ATTR_NICType, m_nic_type);

    // classad -> string
    ClassAdUnParser unparser;
    string str_ad;
    // Serialization, convert ClassAd into string str_ad
    unparser.Unparse(str_ad, &ad);
    
    return str_ad; 
}
