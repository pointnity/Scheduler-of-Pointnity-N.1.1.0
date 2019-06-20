/********************************
 FileName: executor/hdfs_wrapper.cpp
 Version:  0.1
 Description: hdfs wrapper
*********************************/

#include "submitter/hdfs_wrapper.h"

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <gflags/gflags.h>

using log4cplus::Logger;

static Logger logger = Logger::getInstance("submitter");

DECLARE_string(hdfs_host);
DECLARE_int32(hdfs_port);


bool HDFSWrapper::Init() {
    m_local_fs = hdfsConnect(NULL, 0);
    if (NULL == m_local_fs) {
