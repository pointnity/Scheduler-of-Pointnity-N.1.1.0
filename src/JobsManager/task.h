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
        } 
    }

    ClassAdPtr taskad_hard_constraint;  //Task properties, including hard constraint requirements
    list<ClassAdPtr> soft_constraint_list; //Soft constraint list
};

typedef shared_ptr<TaskAd> TaskAdPtr;

class AdjEdge {
public:
    AdjEdge(int32_t e, int32_t w) {
        end = e;
        weight = w;
    }
    int32_t end;
    int32_t weight;
}; 

typedef shared_ptr<AdjEdge> AdjEdgePtr;

class Task : public enable_shared_from_this<Task> {
public:
    virtual void InitTaskInfo(TaskAdPtr ad, int32_t job_id, int32_t task_id, int32_t submit_time = 0);
    void SetTaskHardClassAd();

    TaskState GetTaskState();
    void SetTaskState(int32_t state);
    //void GetTaskStateInfo(const TaskStateInfo& task_state_info);
    bool StartTask(const string& endpoint, const string& taskad);
    void TaskStarting();
    void TaskStarted();
    void TaskFinished();
    void TaskFailed();
    void TaskTimeout();
    void TaskMissed();
    void RestartTask();
    bool IsTimeout();
    bool KillforFT();
    int32_t GetTaskId();
    int32_t GetJobId();
    string GetGroupName();
    int32_t GetRawPriority();
    int32_t GetSchedModel();
    double GetNeedCpu();
    int32_t GetNeedMemory();
    int32_t GetNeedMemory();

    ClassAdPtr GetTaskHardClassAd();
