/********************************
 FileName: ResourceScheduler/resource_scheduler_service.cpp


 Version:  0.1
 Description: resource scheduler service
*********************************/

#ifndef SRC_RESOURCE_SCHEDULER_SERVICE_H
#define SRC_RESOURCE_SCHEDULER_SERVICE_H

#include <string>
#include <list>
#include <vector>
#include "proxy/ResourceScheduler/gen-cpp/ResourceScheduler.h"

using std::string;
using std::vector;

class ResourceSchedulerService : public ResourceSchedulerIf{
public:
    void GetCurVersion(string& new_version);
    int RegistMachine(const string& ip, const string& version);
    int UpdateMachine(const string& heartbeat_ad);
