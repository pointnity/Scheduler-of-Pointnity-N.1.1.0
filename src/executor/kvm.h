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
