/********************************
 FileName: JobsManager/app_manager.cpp
 
 
 Version:  0.1
 Description: app maneger
*********************************/
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>
#include <iostream>
#include <string>

#include "JobsManager/app_manager.h"
#include "common/clynn/rpc.h"
#include "include/proxy.h"

using log4cplus::Logger;
using namespace std;
using clynn::ReadLocker;
using clynn::WriteLocker;

static Logger logger = Logger::getInstance("JobsManager");

bool AppManager::CreateApp(const string& user, const string& name) {
    ReadLocker lock(app_name_to_user_lock);
    map<string, string>::iterator it = app_name_to_user.find(name);

    if(it != app_name_to_user.end()) {
