/*******************************
 File name: submitter/app.cpp
 Version:  0.1
 Description: app 
*********************************/

#include <strstream>
#include <vector>
#include "submitter/app_config.h"
#include "submitter/app_file.h"
#include "submitter/app.h"
#include "include/classad_attr.h"

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using log4cplus::Logger;
using std::string;
using std::strstream;
using std::vector;

static Logger logger = Logger::getInstance("submitter");

bool App::CreateApp(const string& app_config_ad){
    //create app config
    if(false == AppConfigPtrI::Instance()->CreateAppConfig(app_config_ad)){
