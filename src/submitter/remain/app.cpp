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
	LOG4CPLUS_ERROR(logger, "create app faile");
        return false;
    }
    //create app file on hdfs
    string app_file_name;
    string app_file_source;
    string app_file_locate;
    //get value from classad to app_config
    ClassAdParser parser;
    ClassAd* ad_ptr = parser.ParseClassAd(app_config_ad);

    //parse app_file_name
    if (!ad_ptr->EvaluateAttrString(ATTR_APP_FILE_NAME, app_file_name)) {
