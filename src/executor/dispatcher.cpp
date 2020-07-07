/********************************
 FileName: executor/dispatcher.cpp
 Version:  0.1
 Description: dispatcher for events; events -> dispatcher -> handler
*********************************/

#include "executor/dispatcher.h"

// register <EventType::type, Handler*>
void Dispatcher::Register(EventType::type type, Handler* handler) {
    m_handler_map[type] = handler;
}

Handler* Dispatcher::Dispatch(EventType::type type) {
