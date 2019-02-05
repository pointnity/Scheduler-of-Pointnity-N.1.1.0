#ifndef JOBS_MANAGER_JOB_H
#define JOBS_MANAGER_JOB_H

#include <string>
#include <list>
#include <vector>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 5) 
#include <atomic>  // for ubuntu
#else
#include <cstdatomic> // for centos
#endif

#include <boost/shared_ptr.hpp>
#include "common/classad/classad_complement.h"
#include "common/clynn/block_queue.h"
#include "common/clynn/singleton.h"
#include "common/clynn/rwlock.h"
#include "JobsManager/task.h"
#include "JobsManager/job_enum.h"
#include "JobsManager/constraint_edge.h"

using std::string;
using std::list;
using std::vector;
using std::map;
using boost::shared_ptr;
using clynn::BlockQueue;
using clynn::RWLock;
