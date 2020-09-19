/********************************
 FileName: executor/vm.h
 Version:  0.1
 Description: virtual machine, include kvm and lxc
*********************************/

#ifndef SRC_EXECUTOR_VM_H
#define SRC_EXECUTOR_VM_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "include/proxy.h"
#include "include/type.h"
#include "common/clynn/rwlock.h"
#include "executor/task_entity_pool.h"

using std::string;
using boost::shared_ptr;
using clynn::RWLock;

class VM {
public:
    // TODO
    explicit VM(const TaskInfo& info) {
        m_id = info.id;
        m_info = info;
        m_type = info.type;
    }

    ~VM() {}

    TaskID GetID() const;

    string GetName() const;

    VMType::type GetVMType() const;

    TaskInfo GetTaskInfo() const;

    // VMState::type GetState();

    TaskPtr GetTaskPtr();

    //RWLock& GetLock() {
    //    return m_lock;
    // }

    // HbVMInfo GetHbVMInfo();

    bool IsRun() const;

    string GetAppName() const;

    // void SetState(VMState::type state);

    void SetNameByString(string name);

    // key function
    // virtual void SetName();
    virtual int32_t Execute() = 0; // total entry

    virtual int32_t CreateVM() = 0; // create enviroment, kvm or lxc

    //virtual int32_t InstallApp() = 0; // install the app 

    //virtual int32_t StartApp() = 0;  // start the app

    virtual bool Stop() = 0;

    virtual bool Kill() = 0;
