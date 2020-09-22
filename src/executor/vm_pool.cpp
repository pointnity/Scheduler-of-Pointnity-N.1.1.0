/********************************
 FileName: executor/vm_pool.cpp
 Version:  0.1
 Description: the pool of vm, include kvm and lxc
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <classad/classad.h>
#include <classad/classad_distribution.h>
#include "include/classad_attr.h"

#include "executor/vm_pool.h"

using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("executor");

DECLARE_string(libvirt_dir);
DECLARE_string(lxc_dir);
// DECLARE_string(lxc_template);

bool VMPool::Init() {
    // check libvirt work dir
    if (access(FLAGS_libvirt_dir.c_str(), F_OK) == -1) {
        string cmd = "mkdir -p " + FLAGS_libvirt_dir;
        int32_t ret = system(cmd.c_str());
        ret = ret >> 8;
        if (ret != 0) {
           LOG4CPLUS_ERROR(logger, "Failed to create libvirt(kvm) work dir: " << FLAGS_libvirt_dir);
           return false;
        }
    }

    // check lxc work dir
    if (access(FLAGS_lxc_dir.c_str(), F_OK) == -1) {
        string cmd = "mkdir -p " + FLAGS_lxc_dir;
        int32_t ret = system(cmd.c_str());
        ret = ret >> 8;
        if (ret != 0) {
            LOG4CPLUS_ERROR(logger, "Failed to create lxc work dir, cmd: " << cmd);
            return false;
        }
    }

    return true;
}

// TODO just for test
void VMPool::PrintAll() {
    ReadLocker locker(m_lock);
    printf("vm_pool.cpp\n");
    printf("************ VMs ************\n");
    for (map<TaskID, VMPtr>::iterator it = m_vm_map.begin();
         it != m_vm_map.end(); ++it) {
        printf("VM job_id:%d, task_id:%d\n", (it->first).job_id, (it->first).task_id);
    }
    printf("*****************************\n");
}

// insert VMPtr into map and queue
void VMPool::Insert(const VMPtr& ptr) {
    InsertIntoPool(ptr);
    InsertIntoQueue(ptr);
}

// insert VMPtr into map
void VMPool::InsertIntoPool(const VMPtr& ptr) {
    WriteLocker locker(m_lock);
    m_vm_map[ptr->GetID()] = ptr;
    m_vm_state_map[ptr->GetID()] = true;
}

// insert VMPtr into queue
void VMPool::InsertIntoQueue(const VMPtr& ptr) {
    WriteLocker locker(m_lock);
    m_queue.push(ptr);
}
