/********************************
 FileName: executor/service.h
 Version:  0.1
 Description: executor service
*********************************/

#ifndef SRC_EXECUTOR_SERVICE_H
#define SRC_EXECUTOR_SERVICE_H

#include "include/proxy.h"

using std::string;

class ExecutorService : public ExecutorIf {
public:
    int32_t  Helloworld();

    //RS
