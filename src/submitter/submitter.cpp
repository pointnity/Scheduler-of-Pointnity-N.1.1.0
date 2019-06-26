/********************************
 FileName: submitter/submitter.cpp
 Version:  0.1
 Description: submitter main
*********************************/

#include <stdlib.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/configurator.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/layout.h>
#include <gflags/gflags.h>

#include "submitter/cmd_parse.h"


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

// gflag, config for submitter
DECLARE_string(object);//app or job...
DECLARE_string(operation);// create or delete...
/*
DECLARE_int32(app_id);
DECLARE_int32(job_id);
DECLARE_int32(user_id);
DECLARE_int32(image_id);
*/
int main(int argc, char **argv) {
    //is root ?
    if (geteuid() != 0) {
