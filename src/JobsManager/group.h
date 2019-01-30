/********************************
 FileName: JobsManager/group.h
 
 
 Version:  0.2
 Description: group: quota & queues
*********************************/

#ifndef JOBS_MANAGER_GROUP_H
#define JOBS_MANAGER_GROUP_H

#include <list>
#include <boost/shared_ptr.hpp>
#include "common/clynn/singleton.h"
#include "common/clynn/rwlock.h"
#include "proxy/JobsManager/gen-cpp/JobsManager.h"
#include "JobsManager/job.h"

using boost::shared_ptr;
using std::list;
using clynn::RWLock;
using std::string;
