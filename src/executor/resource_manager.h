/********************************
 FileName: executor/resource_manager.h
 Version:  0.1
 Description: resource manager of the machine(execute node)
*********************************/

#ifndef SRC_EXECUTOR_RESOURCE_MANAGER_H
#define SRC_EXECUTOR_RESOURCE_MANAGER_H

#include <string>
#include <map>
#include <vector>
#include <boost/shared_ptr.hpp>

#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "common/clynn/singleton.h"
#include "common/clynn/rwlock.h"

using std::string;
using std::map;
using std::vector;
using boost::shared_ptr;
