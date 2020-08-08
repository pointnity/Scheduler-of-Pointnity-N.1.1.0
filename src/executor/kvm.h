/********************************
 FileName: executor/kvm.h
 Version:  0.1
 Description: kvm, inherit from vm
*********************************/

#ifndef SRC_EXECUTOR_KVM_H
#define SRC_EXECUTOR_KVM_H

#include <sys/time.h>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <gflags/gflags.h>
#include "executor/vm.h"

DECLARE_int32(vm_hb_interval);

class KVM : public VM {
public:
    explicit KVM(const TaskInfo& info) : VM(info) {
        m_domain_ptr = NULL;
        m_timestamp = -1;
	m_running_time = -1;
	m_starting_time = time(NULL);
        m_time_to_death = 10 * FLAGS_vm_hb_interval;
        m_created = false;
        m_installed = false;
    }

    ~KVM() {
        // free domain
        if(m_domain_ptr) {
            virDomainFree(m_domain_ptr);
        }
        // clear the work directory
        if (!m_dir.empty()) {
            string cmd = "rm -r " + m_dir;
            system(cmd.c_str());
        }
    }

    // virtual function, from VM
    int32_t Execute();

    int32_t CreateVM(); // create kvm, and install? TODO

    //int32_t InstallApp();

    //int32_t StartApp();  // Start the task

    bool Stop();

    bool Kill();

    // Judge State
    //VMState::type GetState();

    HbVMInfo GetHbVMInfo();    //get heartbeart

    void SetHbVMInfo(const string& hb_vm_info_ad);

    // unique in KVM 
