/********************************
 FileName: executor/vm.cpp
 Version:  0.1
 Description: virtual machine, include kvm and lxc
*********************************/

#include "executor/vm.h"

using clynn::WriteLocker;
using clynn::ReadLocker;

// public
TaskID VM::GetID() const {
    return m_id;
}

string VM::GetName() const {
    return m_name;
}

VMType::type VM::GetVMType() const {
    return m_type;
}

TaskInfo VM::GetTaskInfo() const {
    return m_info;
}

// VMState::type VM::GetState() {
//    ReadLocker locker(m_lock);
//    return m_state;
// }

TaskPtr VM::GetTaskPtr() {
    return TaskPoolI::Instance()->GetTaskPtr(m_id);
}

bool VM::IsRun() const {
    return m_info.is_run;
}

string VM::GetAppName() const {
    if (!IsRun())
