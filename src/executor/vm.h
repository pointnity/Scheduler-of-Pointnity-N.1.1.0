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
