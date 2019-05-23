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
#include "executor/kvm.h"
#include "executor/lxc.h"

using std::map;
using std::queue;
using std::vector;
using std::tr1::function;
using std::tr1::placeholders::_1;
using std::tr1::placeholders::_2;
using clynn::RWLock;

class VMPool {
public:
    // function pointer, from std::tr1::function
    typedef function<void(VM*)> VMFunc;

    // check & mkdir libvirt & lxc
    bool Init();

    // TODO print all
    void PrintAll();
