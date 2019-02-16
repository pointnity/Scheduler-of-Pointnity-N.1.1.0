/********************************
 FileName: JobsManager/task_cluster.h


 Version:  0.1
 Description: task, include ClassAd m_taskad_hard_constraint and list<ClassAd> m_soft_constraint_list
*********************************/

#ifndef JOBS_MANAGER_TASK_CLUSTER_H
#define JOBS_MANAGER_TASK_CLUSTER_H

#include <boost/shared_ptr.hpp>
#include "common/classad/classad_complement.h"
#include "common/clynn/rwlock.h"
#include "JobsManager/job_enum.h"

using std::list;
using boost::shared_ptr;
using clynn::RWLock;

class TaskCluster {
public:
