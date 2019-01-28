/********************************
 FileName: JobsManager/event.h


 Version:  0.1
 Description: event, and its handler
*********************************/

#ifndef SRC_JOBS_MANAGER_EVENT_H
#define SRC_JOBS_MANAGER_EVENT_H

#include <string>
#include <boost/shared_ptr.hpp>

#include "common/clynn/block_queue.h"
#include "JobsManager/job_enum.h"

using std::string;
using boost::shared_ptr;
using clynn::BlockQueue;

class Event {
public:
    Event(JMEventType type) : m_type(type) {}
    virtual ~Event() {}
