/********************************
 FileName: JobsManager/dispatcher.cpp
 
 
 Version:  0.1
 Description: dispatcher for events; events -> dispatcher -> handler
*********************************/

#include "JobsManager/dispatcher.h"

// register <JMEventType, Handler*>
void Dispatcher::Register(JMEventType type, Handler* handler) {
