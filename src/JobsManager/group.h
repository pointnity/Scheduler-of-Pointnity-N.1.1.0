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

class Group {
public:
    Group(const string& name);
    string GetGroupName();
    // string GetGroupName(const JobQueueNum& queue_num);
    
    // Add Job -> Queue
    bool AddJobToWaitQueue(const JobPtr& job, bool push_front = false);
    bool GetNewJobWaitQueueNum(const JobPtr& job, JobQueueNum& job_queue_num);
    bool AddJobToQueueByQueueNum(const JobPtr& job, const JobQueueNum& num, bool push_front);

    // Select Job From Queue -> Navigating Job
    bool SelectJobToNavigatingJob();
    bool MoveJobToNavigatingJobByQueueNum(const JobQueueNum& num);

    // get Navigating job
