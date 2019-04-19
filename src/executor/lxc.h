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
