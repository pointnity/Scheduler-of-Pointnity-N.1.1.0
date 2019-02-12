/********************************
 FileName: JobsManager/JobsManager.cpp


 Version:  0.1
 Description: JobsManager main
*********************************/
#include <iostream>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <gflags/gflags.h>

#include "include/proxy.h"
#include "common/clynn/rpc.h"
#include "JobsManager/group_pool.h"
#include "JobsManager/jobs_manager_service.h"
#include "JobsManager/dispatcher.h"

using std::string;
using std::cout;
using std::endl;
using std::auto_ptr;

using log4cplus::Logger;
using log4cplus::ConsoleAppender;
using log4cplus::FileAppender;
using log4cplus::Appender;
using log4cplus::Layout;
using log4cplus::PatternLayout;
using log4cplus::helpers::SharedObjectPtr;

DECLARE_int32(jobs_manager_port);
DECLARE_string(resource_scheduler_endpoint);
DECLARE_string(groups_xml);

extern void* NewJobThread(void* unused);
extern void* JobProcessorThread(void* unused);
extern void* TaskCheckerThread(void* unused);
extern void* JobStateUpdaterThread(void* unused);

int main(int argc, char **argv){
    SharedObjectPtr<Appender> append(new FileAppender("../log/JobsManager.log"));
    append->setName(LOG4CPLUS_TEXT("append for JobsManager"));
    auto_ptr<Layout> layout(new PatternLayout(LOG4CPLUS_TEXT("%d{%m/%d/%y %H:%M:%S} %p %l:%m %n")));
    append->setLayout(layout);
    Logger logger = Logger::getInstance(LOG4CPLUS_TEXT("JobsManager"));
    logger.addAppender(append);
    logger.setLogLevel(log4cplus::INFO_LOG_LEVEL);

    if(argc > 1) {
