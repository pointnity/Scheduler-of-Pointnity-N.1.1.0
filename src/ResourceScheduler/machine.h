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
