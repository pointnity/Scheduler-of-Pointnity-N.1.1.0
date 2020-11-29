/********************************
 *  FileName: ResourceScheduler/machine.h
 *
 *********************************/

#ifndef RESOURCE_SCHEDULER_MACHINE_H
#define RESOURCE_SCHEDULER_MACHINE_H

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include "common/classad/classad_complement.h"
#include "common/clynn/rwlock.h"
#include "include/proxy.h"
#include "include/type.h"

using std::map;
using std::string;
using boost::shared_ptr;

using clynn::RWLock;

class Machine {
public:
    Machine(const ClassAdPtr& machine_ad);
    bool ParseMachineAd();
    void Update(const ClassAdPtr& machine_ad);
    string GetMachineEndpoint();
    bool GetMachineByImageInfo(const string& name, const string& user, const int32_t size);
    bool TempAllocResource(const TaskID& id, const AllocResource& alloc_resource);

    void SetId(int id);
    int GetId();
    //int GetTARMapSize();
    //bool CheckAndClearTARMap(const TaskID& task_id);
    bool GetTemproryAllocResourceMap(map<TaskID, AllocResource>& TemproryAllocResourceMap);
    string GetIp();
    ClassAdPtr GetMachineAd();
private:
