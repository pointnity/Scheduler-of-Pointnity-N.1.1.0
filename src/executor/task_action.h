/********************************
 FileName: executor/task_action.h
 Version:  0.1
 Description: task action
*********************************/

#ifndef SRC_EXECUTOR_TASKACTION_H
#define SRC_EXECUTOR_TASKACTION_H

#include <string>
#include <boost/shared_ptr.hpp>

// #include "include/proxy.h"
#include "include/type.h"
#include "common/clynn/rwlock.h"
#include "common/clynn/singleton.h"

class TaskAction {
public:
    // call back
