/********************************
 FileName: JobsManager/task.h


 Version:  0.1
 Description: task, include ClassAd m_taskad_hard_constraint and list<ClassAd> m_soft_constraint_list
*********************************/

#ifndef JOBS_MANAGER_TASK_H
#define JOBS_MANAGER_TASK_H

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "common/classad/classad_complement.h"
#include "common/clynn/rwlock.h"
#include "include/proxy.h"
#include "JobsManager/job_enum.h"

using std::list;
using boost::shared_ptr;
using boost::enable_shared_from_this;
using clynn::RWLock;

class TaskAd {
public:
    TaskAd() {
        taskad_hard_constraint = ClassAdPtr(new ClassAd());
    }

    // deep copy
    TaskAd(const TaskAd& ads) {
        // hard constraint
        taskad_hard_constraint = ClassAdPtr(new ClassAd(*ads.taskad_hard_constraint));
        // soft constraint list
        for (list<ClassAdPtr>::const_iterator it = ads.soft_constraint_list.begin();  
             it != ads.soft_constraint_list.end(); ++it) 
        {
            ClassAdPtr soft_ad = ClassAdPtr(new ClassAd(*(*it)));
            soft_constraint_list.push_back(soft_ad);  
