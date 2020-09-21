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
DECLARE_string(lxc_dir);
// DECLARE_string(lxc_template);

bool VMPool::Init() {
    // check libvirt work dir
    if (access(FLAGS_libvirt_dir.c_str(), F_OK) == -1) {
        string cmd = "mkdir -p " + FLAGS_libvirt_dir;
        int32_t ret = system(cmd.c_str());
        ret = ret >> 8;
        if (ret != 0) {
           LOG4CPLUS_ERROR(logger, "Failed to create libvirt(kvm) work dir: " << FLAGS_libvirt_dir);
           return false;
        }
    }

    // check lxc work dir
    if (access(FLAGS_lxc_dir.c_str(), F_OK) == -1) {
        string cmd = "mkdir -p " + FLAGS_lxc_dir;
        int32_t ret = system(cmd.c_str());
        ret = ret >> 8;
        if (ret != 0) {
            LOG4CPLUS_ERROR(logger, "Failed to create lxc work dir, cmd: " << cmd);
            return false;
        }
