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
