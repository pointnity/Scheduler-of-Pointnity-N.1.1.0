/********************************
 FileName: executor_monitor/work_thread.h
 Version:  0.1
 Description: work thread
*********************************/

#include <stdlib.h>
#include <iostream>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "executor_monitor/restart_executor.h"
#include "executor_monitor/checker.h"

using log4cplus::Logger;

DECLARE_int32(hb_interval);

static Logger logger = Logger::getInstance("executor_monitor");

// thread, monitor executor
void* ExecutorMonitorProcessor(void* unused) {
    while(true) {
       //executor is exist ?
       Checker* checkerptr = new Checker();
       if((checkerptr->IsProcess("executor")) == false) {
