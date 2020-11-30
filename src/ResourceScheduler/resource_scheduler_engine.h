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
