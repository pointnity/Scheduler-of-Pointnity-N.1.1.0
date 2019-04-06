/********************************
 FileName: executor/dispatcher.h
 Version:  0.1
 Description: dispatcher for events; events -> dispatcher -> handler
*********************************/

#ifndef SRC_EXECUTOR_DISPATCHER_H
#define SRC_EXECUTOR_DISPATCHER_H

#include <map>
#include "common/clynn/singleton.h"
#include "executor/handler.h"

using std::map;

class Dispatcher {
public:
