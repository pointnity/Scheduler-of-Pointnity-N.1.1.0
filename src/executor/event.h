/********************************
 FileName: executor/event.h
 Version:  0.1&0.2
 Description: event, and its handler
*********************************/

#ifndef SRC_EXECUTOR_EVENT_H
#define SRC_EXECUTOR_EVENT_H

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
    Event(EventType::type type) : m_type(type)  {}
    virtual ~Event() {}
    virtual bool Handle() = 0;
    EventType::type GetType() const {
        return m_type;
    }
private:
    EventType::type m_type;
};


class TaskEvent : public Event {
public:
    explicit TaskEvent(TaskID id, EventType::type type) : Event(type), m_id(id) {}
    virtual ~TaskEvent() {}
    TaskID GetID() const {
        return m_id;
    }
private:
    TaskID m_id;
}; 


class ImageEvent : public Event {
public:
    ImageEvent(const string& user, const string& name, const int32_t size) : Event(EventType::IMAGE_EVENT),
             m_name(name), m_user(user), m_size(size) {}

    ~ImageEvent() {}
    bool Handle();
    string GetName() const {
        return m_name;
    }
    string GetUser() const {
        return m_user;
    }
    int32_t GetSize() const {
        return m_size;
    }
private:
    string m_name;
    string m_user;
    int32_t m_size;
};

class HeartbeatEvent : public Event {
public:
    HeartbeatEvent(const string&  hb_vm_info_ad) : Event(EventType::HEARTBEAT_EVENT),
             m_hb_vm_info_ad(hb_vm_info_ad) {}

    ~HeartbeatEvent() {}
    bool Handle();
    string GetHbInfo() const {
        return  m_hb_vm_info_ad;
    }
private:
    string  m_hb_vm_info_ad;
};

class ExitExecutorEvent : public Event {
public:
     ExitExecutorEvent() : Event(EventType::EXIT_EXECUTOR_EVENT) {}
    ~ExitExecutorEvent() {}
    bool Handle();
};


class TaskStateEvent : public TaskEvent {
public:
    explicit TaskStateEvent(TaskID id) : TaskEvent(id, EventType::TASK_STATE_EVENT) {}
    virtual ~TaskStateEvent() {}
};

class TaskActionEvent : public TaskEvent {
public:
    explicit TaskActionEvent(TaskID id) : TaskEvent(id, EventType::TASK_ACTION_EVENT) {}
    virtual ~TaskActionEvent() {} 
};
};
