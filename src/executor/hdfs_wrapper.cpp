/********************************
 FileName: executor/hdfs_wrapper.cpp
 Version:  0.1
 Description: hdfs wrapper
*********************************/

#include "executor/hdfs_wrapper.h"
#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

using log4cplus::Logger;

static Logger logger = Logger::getInstance("executor");

DECLARE_string(hdfs_host);
DECLARE_int32(hdfs_port);


bool HDFSWrapper::OpenConnect() {
   try {
           m_local_fs = hdfsConnect(NULL, 0);
           } catch (hdfsFS &tx) {
               LOG4CPLUS_ERROR(logger, "Hdfs connect local error:");
