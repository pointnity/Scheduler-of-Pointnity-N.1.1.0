/********************************
 FileName: resourcescheduler/event.h


 Version:  0.1
 Description: event, and its handler
*********************************/

#ifndef SRC_RESOURCE_SCHEDULER_EVENT_H
#define SRC_RESOURCE_SCHEDULER_EVENT_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "common/clynn/block_queue.h"

#include "include/proxy.h"
#include "include/type.h"

using std::string;
using boost::shared_ptr;
using clynn::BlockQueue;

class Event {
public:
    Event(RSEventType::type type) : m_type(type)  {}
