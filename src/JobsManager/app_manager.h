/********************************
 FileName: executor/app_maneger.h
 
 
 Version:  0.1
 Description: app manager
*********************************/

#ifndef JOB_MANAGER_APP_MANAGER_H
#define JOB_MANAGER_APP_MANAGER_H

#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

#include "common/clynn/singleton.h"
#include "common/clynn/rwlock.h"

using std::map;
using clynn::RWLock;

class AppManager {
