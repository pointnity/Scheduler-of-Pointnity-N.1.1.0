/********************************
 FileName: executor/vm_pool.cpp
 Version:  0.1
 Description: the pool of vm, include kvm and lxc
*********************************/

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include <classad/classad.h>
#include <classad/classad_distribution.h>
#include "include/classad_attr.h"

#include "executor/vm_pool.h"

using log4cplus::Logger;
using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("executor");

DECLARE_string(libvirt_dir);
