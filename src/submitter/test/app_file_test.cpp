/********************************
 FileName: submitter/app_file_test.cpp
 Version:  0.1
 Description: app_file_test main
*********************************/

#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <gflags/gflags.h>

#include "submitter/app_file.h"

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


int main(int argc, char **argv) {

    // initilize log log4cplus
    SharedObjectPtr<Appender> append(new FileAppender("submitter.log"));
    append->setName(LOG4CPLUS_TEXT("append for submitter"));
