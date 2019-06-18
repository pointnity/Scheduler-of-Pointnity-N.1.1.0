/*******************************
 File name: submitter/cmd_parse.cpp
 Version:  0.1
 Description: cmd parse
*********************************/

#include "submitter/cmd_parse.h"
#include "submitter/image.h"
#include "submitter/app.h"
#include "submitter/job.h"

#include <iostream>
#include <gflags/gflags.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using log4cplus::Logger;
using std::cout;
using std::endl;

static Logger logger = Logger::getInstance("submitter");

DECLARE_string(operation);// create or delete...
DECLARE_string(xml_path); //classad string 
