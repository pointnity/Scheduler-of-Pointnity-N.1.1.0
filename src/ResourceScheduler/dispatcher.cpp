/********************************
 FileName: ResourceScheduler/dispatcher.cpp


 Version:  0.1
 Description: dispatcher for events; events -> dispatcher -> handler
*********************************/

#include "ResourceScheduler/dispatcher.h"

// register <EventType::type, Handler*>
void Dispatcher::Register(RSEventType::type type, Handler* handler) {
