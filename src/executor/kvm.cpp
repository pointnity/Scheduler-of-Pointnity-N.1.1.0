/********************************
 FileName: executor/kvm.cpp
 Version:  0.1
 Description: kvm, inherit from vm
*********************************/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "common/rapidxml/rapidxml.hpp"
#include "common/rapidxml/rapidxml_utils.hpp"
#include "common/rapidxml/rapidxml_print.hpp"
#include "common/clynn/rpc.h"

#include <classad/classad.h>
#include <classad/classad_distribution.h>
#include "include/classad_attr.h"

#include "include/proxy.h"
#include "executor/hdfs_wrapper.h"
#include "executor/kvm.h"
#include "executor/task_entity_pool.h"
#include "executor/resource_manager.h"
#include "executor/dispatcher.h"
#include "executor/image_manager.h"
#include "executor/vm_pool.h"

using std::cout;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::endl;
using namespace rapidxml;
using namespace std;
using log4cplus::Logger;
using clynn::WriteLocker;
using clynn::ReadLocker;

// gflag 
DECLARE_string(libvirt_dir);
DECLARE_string(xml_template);
DECLARE_int32(vm_hb_interval);
DECLARE_string(hdfs_host);
DECLARE_int32(hdfs_port);
DECLARE_bool(debug);
DECLARE_int32(starting_timeout);

static Logger logger = Logger::getInstance("executor");

string KVM::m_xml_template = "";
virConnectPtr KVM::m_conn = NULL;


/// @brief: public function
// KVM & ~KVM are inplement in kvm.h

/// virtual function, from V
// virtual C, include CreateVM and Install 
int32_t KVM::Execute() {
    if (CreateVM() != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to create kvm, name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id); 
        return -1;
    }
    return 0;
}

// create vm
int32_t KVM::CreateVM() {
    if (CreateKVM() != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to create kvm, name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return -1;
    }

    if (SetVNetByXML() != 0) {
        LOG4CPLUS_ERROR(logger, "Failed to set vnet by xml, name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return -1;
    }
    return 0;
}

bool KVM::Stop() {
    return true;
}

bool KVM::Kill() {
    if(FLAGS_debug){
        LOG4CPLUS_DEBUG(logger, "Kill KVM, name:" << GetName());
        // delete work dir
        ifstream in_file(m_dir.c_str(), ios::in);

        //open file error ?
        if(in_file){
            string cmd = "rm -r " + m_dir;
            system(cmd.c_str());
        }
	return true;
    }
    if (!m_domain_ptr) {
        LOG4CPLUS_ERROR(logger, "Invalid domain pointer, Kill VM directly.");
        // delete work dir
        string cmd = "rm -r " + m_dir;
        system(cmd.c_str());
        return true;
    }

    if (virDomainDestroy(m_domain_ptr) != 0) {
        virErrorPtr error = virGetLastError();
        LOG4CPLUS_ERROR(logger, error->message);
        LOG4CPLUS_ERROR(logger, "Can't kill kvm, name:" << GetName() << ", job_id:" << GetID().job_id << ", task_id:" << GetID().task_id);
        return true;
    }

    // delete work dir
     // delete work dir
    ifstream in_file(m_dir.c_str(), ios::in);

    //open file error ?
    if(in_file){
        string cmd = "rm -r " + m_dir;
        system(cmd.c_str());
    }
    return true;
}

HbVMInfo KVM::GetHbVMInfo(){
    TaskID id = GetID();
    TaskPtr task_ptr = GetTaskPtr();
    TaskEntityState::type task_state = task_ptr->GetState();
    if (task_state == TaskEntityState::TASKENTITY_WAITING || task_state == TaskEntityState::TASKENTITY_STARTING){
	if(time(NULL) - m_starting_time > FLAGS_starting_timeout) {
	    //set vm state is false
	    VMPoolI::Instance()->SetVMStateByTaskID(id, false);
	    // new timeoutActionEvent
            EventPtr event(new TimeoutTaskEvent(id));
            // Push event into Queue
            EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
	}
        HbVMInfo empty;
        empty.id = GetID();
        empty.cpu_usage = 0;
        empty.memory_usage = 0;
        empty.bytes_in = 0;
        empty.bytes_out = 0;
        if(task_state == TaskEntityState::TASKENTITY_WAITING) {
              empty.app_state = AppState::APP_WAITING;
        } else {
              empty.app_state = AppState::APP_STARTING;
        }
	return empty;
    } else if(task_state == TaskEntityState::TASKENTITY_FAILED || task_state == TaskEntityState::TASKENTITY_FINISHED) {
	ReadLocker locker(m_lock);
        return m_hb_vm_info;
    } else if(task_state == TaskEntityState::TASKENTITY_RUNNING) {
	int32_t timeout = GetTaskInfo().timeout;
	if(time(NULL) - m_running_time > timeout) {
	    HbVMInfo empty;
            empty.id = GetID();
            empty.cpu_usage = 0;
            empty.memory_usage = 0;
            empty.bytes_in = 0;
            empty.bytes_out = 0;
            empty.app_state = AppState::APP_MISSED;
	    //set vm state is false
            VMPoolI::Instance()->SetVMStateByTaskID(id, false);
            // update task  state into missed
            // new timeoutActionEvent
            EventPtr event(new TimeoutTaskEvent(id));
            // Push event into Queue
            EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
            return empty;

	}

	if ((m_timestamp != -1) && (time(NULL) - m_timestamp > m_time_to_death)) {
            HbVMInfo empty;
            empty.id = GetID();
            empty.cpu_usage = 0;
            empty.memory_usage = 0;
            empty.bytes_in = 0;
            empty.bytes_out = 0;
            empty.app_state = AppState::APP_MISSED;
	    //set vm state is false
            VMPoolI::Instance()->SetVMStateByTaskID(id, false);

            // update task  state into missed
            // new missedActionEvent
            EventPtr event(new MissedTaskEvent(id));
            // Push event into Queue
            EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
            return empty;
         } else {
	    ReadLocker locker(m_lock);
	    return m_hb_vm_info;
         } 
    }else {
