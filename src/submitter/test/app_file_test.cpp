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
