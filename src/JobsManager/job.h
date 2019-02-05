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
using std::atomic_int;

class Job {
public:
    Job();
    void Init(const ClassAdPtr& classad, bool constraints_among_tasks = false);
    void InitTasks(const list<TaskAdPtr>& task_ad_list);
    void InitTasks(const list<TaskAdPtr>& task_ad_list, const list<EdgePtr>& edge_list);
    void SetWaitTime();
    void SetRunTime();
    void UpdateTimeByState(const TaskState& state);
    virtual TaskPtr NewTask() const = 0;
    virtual bool HaveWaitingTasks() = 0;    
    virtual bool IsScheduling() = 0;
    virtual bool IsRunning() = 0;
    string GetGroupName();
    int32_t GetRawPriority();
    int32_t GetSchedModel();
    int32_t GetState(); 
    void SetState(int32_t state);
    int32_t GetJobId();
    double GetNeedCpu();
    int32_t GetNeedMemory(); 
    TaskPtr GetTaskPtr(int32_t task_id);
    int32_t GetRunTaskNum();
    int32_t GetTaskNum();
    void CheckTasks();
    void UpdateState();

    //is a similar mechanism implemented?
    JobQueueNum GetJobQueueNum();

    list<TaskPtr> GetTaskList();
  
    bool GetConstraintsAmongTasks();

    void GetTaskStateInfo(vector<TaskStateInfo>& task_state_info_list);
    // test & TODO
    void PrintAllTasks();

    // constraints among tasks
    string ReadMap(const int32_t task_id);
