/********************************
 FileName: ResourceScheduler/resource_scheduler_service.cpp


 Version:  0.1
 Description: resource scheduler service
*********************************/


#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "include/proxy.h"
#include "common/clynn/rpc.h"

#include "ResourceScheduler/resource_scheduler_service.h"
#include "ResourceScheduler/resource_scheduler_engine.h"
#include "ResourceScheduler/match_maker.h"
#include "ResourceScheduler/dispatcher.h"

#include <iostream>
#include <sstream>
#include <string>

using std::string;
using std::stringstream;
using log4cplus::Logger;
static Logger logger = Logger::getInstance("ResourceScheduler");

void ResourceSchedulerService::GetCurVersion(string& new_version) {
    return COLLECTOR_ENGINE::Instance()->GetCurVersion(new_version);
}

int ResourceSchedulerService::RegistMachine(const string& ip, const string& version) {
    LOG4CPLUS_INFO(logger, "regist machine ip:" << ip);
    return COLLECTOR_ENGINE::Instance()->RegistMachine(ip, version);
}


int ResourceSchedulerService::UpdateMachine(const string& heartbeat_ad){
    LOG4CPLUS_INFO(logger, "a new update:" << heartbeat_ad);
    return COLLECTOR_ENGINE::Instance()->UpdateMachine(heartbeat_ad);
}

int ResourceSchedulerService::NewUpdateMachine(const string& heartbeat_ad, const vector<string>& task_list){
    // new MachineUpdateEvent
    EventPtr event(new MachineUpdateEvent(heartbeat_ad, task_list));
    // Push event into Queue
    EventDispatcherI::Instance()->Dispatch(event->GetType())->PushBack(event);
    return 0;
}


int ResourceSchedulerService::DeleteMachine(const string& ip){
     // new MachineUpdateEvent
    EventPtr event(new MachineDeleteEvent(ip));
    // Push event into Queue
