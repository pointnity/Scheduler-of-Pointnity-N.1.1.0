/********************************
 FileName: executor/vm_pool.h
 Version:  0.1
 Description: the pool of vm, include kvm and lxc
*********************************/

#ifndef SRC_EXECUTOR_VM_POOL_H
#define SRC_EXECUTOR_VM_POOL_H

#include <map>
#include <queue>
#include <vector>
#include <tr1/functional>
#include <sys/types.h>

#include "common/clynn/singleton.h"
#include "common/clynn/rwlock.h"
#include "executor/vm.h"
