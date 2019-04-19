/********************************
 FileName: executor/lxc.h
 Version:  0.1
 Description: lxc(Linux Container), inherit from vm
*********************************/

#ifndef SRC_EXECUTOR_LXC_H
#define SRC_EXECUTOR_LXC_H

#include "sys/types.h"
#include "executor/vm.h"

class LXC : public VM {
public:
    explicit LXC(const TaskInfo& info) : VM(info) {
        m_first = true;
        m_prev_cpu = 0.0;
        m_prev_total = 0.0;
    }

    ~LXC() {
        // clear the work directory
        if (!m_dir.empty()) {
            string cmd = "rm -r " + m_dir;
            system(cmd.c_str());
        }    
    }

    // virtual function, from VM
    int32_t Execute();

    int32_t CreateVM(); // create LXC

    // TODO
    int32_t InstallApp();

    // @brief: fork process and run the task
    int32_t StartApp();

    bool Stop();

    bool Kill();

    //VMState::type GetState();

    HbVMInfo GetHbVMInfo();    //get heartbeart

    void SetHbVMInfo(const string& hb_vm_info_ad);

    pid_t GetPid();

    string GetVeth();
private:
    // virtual function, from VM
    void SetName();

    bool SetVeth();

    // set Member Variable 
    int32_t Init();
