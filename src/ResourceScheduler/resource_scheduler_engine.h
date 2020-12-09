/********************************
 FileName: ResourceScheduler/resource_scheduler_engine.h


 Version:  0.1
 Description: resource scheduler engine
*********************************/

#ifndef SRC_RESOURCE_SCHEDULER_ENGINE_H
#define SRC_RESOURCE_SCHEDULER_ENGINE_H

#include <map>
#include <set>
#include <vector>
#include <string>
#include <stdint.h>
#include <tr1/functional>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 5) 
#include <atomic>  // for ubuntu
#else
#include <cstdatomic> // for centos
#endif

#include "common/clynn/singleton.h"
#include "common/clynn/rwlock.h"
#include "common/classad/classad_complement.h"
#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"
#include "ResourceScheduler/machine.h"
#include "ResourceScheduler/machine_constances.h"

using std::map;
using std::string;
using std::set;
using std::vector;
using clynn::RWLock;
using std::tr1::function;
using std::atomic_int;

class ResourceSchedulerEngine {
    public:
        ResourceSchedulerEngine();
        ~ResourceSchedulerEngine();
        int Init();
	void GetCurVersion(string& new_version);
	int RegistMachine(const string& ip, const string& version);
        int UpdateMachine(const string& machine_ad);
	int NewUpdateMachine(const string& machine_ad, const vector<string>& task_list);
        int DeleteMachine(const string& ip);
        // get total resource including cpu, memory, disk. service for JobsManager
