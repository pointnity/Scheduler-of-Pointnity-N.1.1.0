/*******************************
 File name: submitter/app_file.cpp
 Version:  0.1
 Description: app file
*********************************/

#include <fstream>
#include <iostream>
#include <sstream>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

#include "submitter/app_file.h"
#include "include/hdfs.h"

using log4cplus::Logger;
using std::string;
using std::ifstream;
using std::ios;
using std::ostringstream;

static Logger logger = Logger::getInstance("submitter");

bool AppFile::CreateAppFile(const string& app_file_name, const string& app_file_locate, const string& app_file_source){
    //get endpoint from zookeeper

    //connect hdfs
    hdfsFS fs = hdfsConnect("localhost",9000 );
    if(!fs) {
