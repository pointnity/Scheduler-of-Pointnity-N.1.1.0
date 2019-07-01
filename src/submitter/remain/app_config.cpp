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
        LOG4CPLUS_ERROR(logger, "create app faile,app_config_ad is null");
	return false;
    }
    //get rpc to create app config
    try {
           Proxy<MasterClient> proxy = Rpc<MasterClient, MasterClient>::GetProxy("localhost:9999");
	   app_id = proxy().CreateApp(app_config_ad);
           if(app_id == -1) {
               //std::cout<< "rpc error"<<std::endl;
	       LOG4CPLUS_ERROR(logger, "create app faile, master error");
               return false;
           }
       }  catch (TException &tx) {
          //std::cout<< "rpc error"<<std::endl;
	  LOG4CPLUS_ERROR(logger, "create app faile,rpc error");
