/*******************************
 File name: submitter/app_config.cpp
 Version:  0.1
 Description: app config 
*********************************/

#include <strstream>
#include <vector>
#include "submitter/app_config.h"
#include "include/classad_attr.h"
#include "include/proxy.h"
#include "common/clynn/rpc.h"

#include <classad/classad.h>
#include <classad/classad_distribution.h>

#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>

using log4cplus::Logger;
using std::string;
using std::strstream;
using std::vector;

static Logger logger = Logger::getInstance("submitter");

bool AppConfigI::CreateAppConfig(const string& app_config_ad){
    int32_t app_id;
    //app_config_ad is not null
    if(app_config_ad.empty()){
