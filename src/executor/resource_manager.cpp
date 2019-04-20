/********************************
 FileName: executor/resource_manager.cpp
 Version:  0.1
 Description: resource manager of the machine(execute node)
*********************************/

#include <stdlib.h>
#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include "common/classad/classad_complement.h"
#include "include/classad_attr.h"
#include "include/type.h"
#include "executor/system.h"
#include "executor/vm_pool.h"
#include "executor/image_manager.h"
#include "executor/resource_manager.h"

using std::cout;
using std::endl;
using std::stringstream;
using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

DECLARE_int32(port);
DECLARE_string(resource_scheduler_endpoint);
DECLARE_string(interface);
DECLARE_string(if_bridge);
