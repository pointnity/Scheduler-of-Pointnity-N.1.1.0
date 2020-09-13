/********************************
 FileName: executor/task_entity_pool.h
 Version:  0.1
 Description: the pool of taskentitys
*********************************/

#ifndef SRC_EXECUTOR_TASKENTITY_POOL_H
#define SRC_EXECUTOR_TASKENTITY_POOL_H

#include <map>
// tr1 is lib of c++ std
#include <tr1/memory>
#include <tr1/functional>

#include "common/clynn/rwlock.h"
#include "common/clynn/singleton.h"
#include "executor/task_entity.h"
