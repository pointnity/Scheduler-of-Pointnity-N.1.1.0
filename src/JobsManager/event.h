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
    virtual bool Handle() = 0;
    JMEventType GetType() const {
        return m_type;
    }
private:
    JMEventType m_type;
};

class ImageEvent : public Event {
public:
    ImageEvent(const string& user, const string& name, const int32_t size, bool is_update_all) : Event(JMEventType::IMAGE_EVENT),
             m_name(name), m_user(user), m_size(size), m_is_update_all(is_update_all) {}
    
    ~ImageEvent() {}
    bool Handle();
    string GetName() const {
        return m_name;
    }
    string GetUser() const {
